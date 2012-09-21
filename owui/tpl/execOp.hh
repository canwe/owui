#ifndef _OWUI_TPL_EXEC_OP_HH_
#define _OWUI_TPL_EXEC_OP_HH_

#include <owui/tpl/base.hh>
#include <owui/tpl/codeOp.hh>
#include <olibs/rto/dynamic.hh>
#include <olibs/base/optr.hh>
#include <owui/tpl/code.hh>
#include <owui/tpl/opParametrs.hh>


namespace Owui {
namespace Tpl {


class Code;  


class ExecOp : public OpWithNodes
{
public:
  ExecOp(const String& tagName, const OpParametrs& params);
  
  const String& tagName() const {return m_tagName;}
  String name() const {return m_tagName.substr(1, String::npos);}
  
  virtual void exec(Ostream& os, DynamicContext& dctx) const;
  virtual void print(Ostream& os, const String& prefix = "" ) const;
  virtual void attachSubNode(CodeOp* op){m_code.put(op);}; 

private:
  OpParametrs m_params;
  String      m_tagName;
  Code        m_code;
};


class RootNodeCodeAdapter : public OpWithNodes
{
public:
  RootNodeCodeAdapter(Code& code);
  RootNodeCodeAdapter(const RootNodeCodeAdapter&);
  RootNodeCodeAdapter& operator=(const RootNodeCodeAdapter&);
  
  virtual void attachSubNode(CodeOp* op);
  
private:  
  virtual void exec(Ostream& os, DynamicContext& dctx) const {};  
  virtual void print(Ostream& os, const String& prefix = "" ) const {};  
  
private:
  Code& m_code;
};


} // namespace Tpl
} // namespace Owui

#endif // _OWUI_TPL_EXEC_OP_HH_

