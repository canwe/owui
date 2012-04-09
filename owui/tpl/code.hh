#ifndef _OWUI_TPL_CODE_HH_
#define _OWUI_TPL_CODE_HH_

#include <owui/tpl/tag.hh>
#include <owui/tpl/base.hh>
#include <list>


namespace Owui {
namespace Tpl {

class CodeOp;
class VarOp;

class Code
{
public:
  typedef std::list<CodeOp*> Commands;
  typedef std::list<VarOp*> Variables;
  
public:
  ~Code();
  
  const Commands& commands() const {return m_commands;}
  void put(CodeOp* op){m_commands.push_back(op);}
  void print(Ostream& os, const String& prefix = "") const;
  void putVariable(VarOp* op){}
  void registrateVariable(VarOp* var);

  void chex(const TagInfo& tagInfo)const;
  
private:
  Commands m_commands;
  Variables m_variables;
  
}; // class Code


} // namespace Tpl
} // namespace Owui

#endif // _OWUI_TPL_CODE_HH_

