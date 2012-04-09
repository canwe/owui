#ifdef OWUI_DEBOUT_TPL_PARSER
#define OLIBS_DEBOUT_ENABLE 1
#else
#define OLIBS_DEBOUT_ENABLE 0
#endif

#include <owui/tpl/parser.hh>
#include <owui/tpl/code.hh>
#include <owui/tpl/textOp.hh>
#include <owui/tpl/staticContext.hh>
#include <owui/tpl/parametrParser.hh>
#include <olibs/base/optr.hh>
#include <olibs/str/tokenizer.hh>
#include <olibs/str/ut.hh>
#include <owui/tpl/varOp.hh>
#include <sstream>
#include <algorithm>
#include <deque>



namespace Owui {
namespace Tpl {


ParserEx::ParserEx(const String& text):
  StrEx("Parser ex: " + text)
{}

Parser::Parser(Txt::Text& source, Code& code/*, const StaticContext& codeCtx*/):
  m_source(source),
  m_sourceIter(source),
  m_code(code), 
//  m_codeCtx(codeCtx), 
  m_rootOp(m_code)
{
  reset();

  OpenTag anOpenTag(&m_rootOp);
  m_openTagStack.push(anOpenTag);
}

Parser::~Parser()
{ 
  // if stack elements amount > 1 it is error in *.wut file
  // but if elements amount != 1 it is error in programms logic (only root node (m_rootOp) must remain)
  if(m_openTagStack.size() > 1)
  {
    String what = "unclosed tag: ";
    
    OLIBS_ASSERT(dynamic_cast<ExecOp*>(m_openTagStack.top().m_op) != 0);
    ExecOp* op = static_cast<ExecOp*>(m_openTagStack.top().m_op);
    what += op->name();
    
    throw ParserEx(what);
  }
  OLIBS_ASSERT(m_openTagStack.size() == 1);
}

void Parser::reset()
{
  m_sourceIter.reset();
}

void Parser::parse()
{
  reset();
  
  Txt::Pos textStart = m_sourceIter.pos();
  bool opFound = false;
  
  do
  {
    Op op;
    opFound = getOp(op);
    
    
    if(opFound)
    {
      emitTextCode(fragmentAsStr(m_source, textStart, op.m_startPos));
      textStart = m_sourceIter.pos();
      
      doOp(op);
    }
    else
    {
      emitTextCode(fragmentAsStr(m_source, textStart));
    }    
  }
  while(opFound);
}

bool Parser::getOp(Op& op)
{
  static const Char* opTagStart = "<:";
  static const Char* opVarStart = "${";
  
  static const Char* opStartStrs[] = {opTagStart, opVarStart, 0};
  static const Char* opEndStrs[] = {":>", "}", 0};
  
  Txt::Pos opStartPos;

  int strIdx = -1;
  op.m_startPos = findOneOfStr(m_sourceIter, opStartStrs, &strIdx);
  
  if(strIdx != -1)
  { // str is found
    OLIBS_ASSERT(strIdx >= 0 && size_t(strIdx) < sizeof(opStartStrs)/sizeof(const Char*) - 1);
    
    opStartPos = m_sourceIter.pos();
    Txt::Pos opEndPos = findStr(m_sourceIter, opEndStrs[strIdx]);
    
    
    if(String(opStartStrs[strIdx]) == String(opTagStart))
      op.m_type = Op::otTag;
    else if(String(opStartStrs[strIdx]) == String(opVarStart))
      op.m_type = Op::otVar;
    else
      OLIBS_ASSERT(false);
    
    if(opEndPos == Null())
    {
      Olibs::String what = "can not find the end of operator";
      putError(opStartPos, what);
      throw ParserEx(what);
    }
    else
     parseOp(Str::truncate(fragmentAsStr(m_source, opStartPos, opEndPos)), op);
  }
  
  return opStartPos != Null();
}

void Parser::putError(const Txt::Pos& pos, const String& text)
{
  OLIBS_DEBOUT(text);
  m_errors.push_back(Error(pos, text));
}

void Parser::parseOp(const String& text, Op& tag)
{
  OLIBS_DEBOUT("parseOp: " + text);
  
  if(tag.m_type == Op::otVar)
  {
    tag.m_tag.m_name = text;
  }
  else
  {
    std::deque<String> tagParts;
    splitTag(text, tagParts);
    parseTagName(tagParts, tag);
    parseTagParametrs(tagParts, tag);    
  }
}

void Parser::splitTag(const String& text, std::deque<String>& params)
{
  params.clear();
 
  Olibs::Str::Tokenizer tok(text, ' ');
  for(Olibs::Str::Tokenizer::iterator it = tok.begin(); it != tok.end(); ++it)
    if(*it != "")
      params.push_back(*it); 
}

void Parser::parseTagName(std::deque<String>& params, Op& tag)
{
  String tagName = params.front();
  params.pop_front();

  tag.m_tag.m_isClosing = (tagName[0] == '/');
  if(tag.m_tag.m_isClosing)
    tagName = tagName.substr(1, String::npos);
  
  tag.m_tag.m_name = tagName;
  
  tag.m_tag.m_isClosed = (params.back() == "/");
  if(tag.m_tag.m_isClosed)
    params.pop_back();
  
  if((tag.m_tag.m_isClosing) && (tag.m_tag.m_isClosed))
  {
    String what = "unrecognised tag format";
    putError(tag.m_startPos, what);
    
    throw ParserEx(what);
  }
}

void Parser::parseTagParametrs(std::deque<String>& params, Op& tag)
{
  ParametrParser aParametrParser;
  
  typedef std::deque<String> Parameters; 
  for(Parameters::iterator pos = params.begin(); pos != params.end(); ++pos)
  {
    std::pair<String, String> preParsedParams;
    
    try
    {
      parseParametrs(*pos, preParsedParams);
      tag.m_tag.m_parametrs.add(OpNameValueParamsPair(aParametrParser.exec(preParsedParams.first), aParametrParser.exec(preParsedParams.second)));
    }
    catch(ParserEx& ex)
    {
      putError(tag.m_startPos, ex.what());
      throw;
    }
  }  
}

void Parser::parseParametrs(const String& params, std::pair<String, String>& parsedParams)
{
  std::vector<String> parametrs;
  Olibs::Str::Tokenizer tok(params, '=');
   
  for(Olibs::Str::Tokenizer::iterator it = tok.begin(); it != tok.end(); ++it)
    if(*it != "")
      parametrs.push_back(*it);
   
  parsedParams.first = parametrs.at(0);
  String value = parametrs.at(1);   

  String::iterator begin = std::find(value.begin(), value.end(), '"');
  if(begin == value.end())
    throw ParserEx("Cannot find open of paramtr value");
   
  String::iterator end = std::find(begin, value.end(), '"');
  if(end == value.end())
    throw ParserEx("Cannot find close of paramtr value");  
   
  value.erase(std::remove(value.begin(), value.end(), '"'), value.end());   
  parsedParams.second = value;
}

void Parser::doOp(Op& tag)
{
  if(tag.m_type == Op::otVar)
    doVarOp(tag);
  else if(tag.m_type == Op::otTag)
    doTagOp(tag);
  else OLIBS_ASSERT(false);
}

void Parser::doTagOp(Op& tag)
{
  OLIBS_ASSERT(tag.m_type == Op::otTag);
  
  if(tag.m_tag.m_isClosing)
    doClosingTagOp(tag);
  else
    doOpeningTagOp(tag);
}

void Parser::doOpeningTagOp(Op& tag)
{
  ExecOp* operand = new ExecOp(tag.m_tag.m_name, tag.m_tag.m_parametrs);
  
  if(tag.m_tag.m_isClosed)
  {
    m_openTagStack.top().m_op->attachSubNode(operand);
  }
  else
  {
    m_openTagStack.top().m_op->attachSubNode(operand);
    m_openTagStack.push(operand);
  }  
}

void Parser::doClosingTagOp(Op& tag)
{
  if(m_openTagStack.size() == 1)
  {
    String what;
    what += "unexpected closing tag: " + tag.m_tag.m_name;
    putError(tag.m_startPos, what);
    throw ParserEx(what);
  }
  OLIBS_ASSERT(m_openTagStack.size() > 0);
  
  OLIBS_ASSERT(dynamic_cast<ExecOp*>(m_openTagStack.top().m_op) != 0);
  ExecOp* op = static_cast<ExecOp*>(m_openTagStack.top().m_op);
     
  if(op->name() != tag.m_tag.m_name)
  {
    String what;
    what += "unexpected closing tag: " + tag.m_tag.m_name + " " + op->name() + " expected";
    putError(tag.m_startPos, what);
    throw ParserEx(what);
  }
  
  m_openTagStack.pop();  
}

void Parser::doVarOp(Op& tag)
{
  OLIBS_ASSERT(tag.m_type == Op::otVar);
  
  CodeOp* operand = new VarOp(tag.m_tag.m_name);
  m_openTagStack.top().m_op->attachSubNode(operand);
  
  m_code.registrateVariable(static_cast<VarOp*>(operand));
}

void Parser::emitTextCode(const String& text)
{
  //String pureText = Str::truncate(text);
  //if(pureText == "")
  //  return;
  
  OLIBS_DEBOUT("emitTextCode: '" + text + "'");
  m_openTagStack.top().m_op->attachSubNode(new TextOp(text));
}

} // namespace Tpl
} // namespace Owui

