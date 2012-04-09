#ifndef _OWUI_TPL_PARSER_HH_
#define _OWUI_TPL_PARSER_HH_

#include <owui/tpl/base.hh>
#include <owui/tpl/staticContext.hh>
#include <olibs/base/exception.hh>
#include <olibs/rto/dynamic.hh>
#include <olibs/txt/text.hh>
#include <owui/tpl/execOp.hh>
#include <owui/tpl/opParametrs.hh>
#include <vector>
#include <stack>
#include <deque>


namespace Owui {
namespace Tpl {


class ParserEx: public StrEx
{
public:
  ParserEx(const String& text);
};

struct FullTag
{
  String   m_name;
  bool     m_isClosing;
  bool     m_isClosed;
  OpParametrs m_parametrs;
};

struct Op
{
  enum Type {otTag = 0, otVar = 1};
  Type     m_type;
  Txt::Pos m_startPos;
  FullTag  m_tag;
};

class Parser
{
public:
  struct Error
  {
    Txt::Pos m_pos;
    String   m_text;
    Error(const Txt::Pos& pos, const String& text) {m_pos = pos; m_text = text;}
  };
  
  struct OpenTag
  {
    OpenTag(OpWithNodes* op) : m_op(op){};
    OpWithNodes* m_op;
  };
  
  typedef std::vector<Error> Errors;
  typedef std::stack<OpenTag> OpenTagStack;
  
  Parser(Txt::Text& source, Code& code/*, const StaticContext& sctx*/);
  ~Parser();

  void parse();
  Parser& operator() () {parse(); return *this;}

  const Txt::Text& source() const {return m_source;}
  const Errors& errors() const    {return m_errors;}  

private:
  void reset();
  bool getOp(Op& op);
  void emitTextCode(const String& text);
  void doOp(Op& tag);
  void putError(const Txt::Pos& pos, const String& text);
  void parseOp(const String& text, Op& tag);
  void splitTag(const String& text, std::deque<String>& params);
  void parseTagName(std::deque<String>& params, Op& tag);
  void parseTagParametrs(std::deque<String>& params, Op& tag);
  void doTagOp(Op& tag);
  void doVarOp(Op& tag);
  void parseParametrs(const String& params, std::pair<String, String>& parsedParams);
  void doClosingTagOp(Op& tag);
  void doOpeningTagOp(Op& tag);
  
  
private:  
  Txt::Text&            m_source;
  Txt::CharIter         m_sourceIter;
  Code&                 m_code;
  Errors                m_errors;
//  const StaticContext&  m_codeCtx;
  RootNodeCodeAdapter   m_rootOp;
  OpenTagStack          m_openTagStack;  
};


} // namespace Tpl
} // namespace Owui

#endif // _OWUI_TPL_PARSER_HH_
