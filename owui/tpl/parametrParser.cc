#include <owui/tpl/parametrParser.hh>
#include <owui/tpl/parser.hh>
#include <owui/tpl/textOp.hh>
#include <owui/tpl/varOp.hh>


namespace Owui {
namespace Tpl {

  
const Olibs::String ParametrParser::m_queryStart = "${";
const Olibs::String ParametrParser::m_queryEnd = "}";  
  
void ParametrParser::reset(const Olibs::String& processedString)
{
  m_result.clear();
  m_processedString = processedString;
}
  
OpParametr ParametrParser::exec(const Olibs::String& parametr)
{
  reset(parametr);
  
  size_t textStart = 0;
  bool opFound = false;
  do
  {
    size_t queryStartPos = 0;
    size_t queryAfterEndPos = 0;
    opFound = findQuery(queryStartPos, queryAfterEndPos, textStart);

    if(opFound)
    {
      emitTextCode(textStart, queryStartPos - textStart);
      emitQueryCode(queryStartPos + m_queryStart.size(), queryAfterEndPos - (queryStartPos + m_queryEnd.size() + m_queryStart.size()));
      textStart = queryAfterEndPos;
    }
    else
      emitTextCode(textStart, Olibs::String::npos);

  } while(opFound);
  
  return m_result;
}
  
bool ParametrParser::findQuery(size_t& startPos, size_t& afterEndPos, size_t currentPosition)
{  
  startPos = m_processedString.find(m_queryStart, currentPosition);
  
  if(startPos == Olibs::String::npos)
    return false;
  
  size_t endPos = m_processedString.find(m_queryEnd, startPos);
  
  if(endPos == Olibs::String::npos)
    throw ParserEx("can not find the end of operator");
    
  afterEndPos = endPos + m_queryEnd.size();
  
  return true;
}

void ParametrParser::emitTextCode(size_t startPos, size_t size)
{
  Olibs::String data = m_processedString.substr(startPos, size);
  
  if(data == "")
    return;

  OLIBS_DEBOUT("ParametrParser::emitTextCode: '" + data + "'");
  
  TextEmittingOp* op = new TextOp(data);
  m_result.addPart(op);
}

void ParametrParser::emitQueryCode(size_t startPos, size_t size)
{
  Olibs::String data = m_processedString.substr(startPos, size);
  
  if(data == "")
    throw ParserEx("query is empty");
  
  OLIBS_DEBOUT("ParametrParser::emitQueryCode: '" + data + "'");
  
  TextEmittingOp* op = new VarOp(data);
  m_result.addPart(op);
}



  
}}


