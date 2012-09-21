#ifndef _OWUI_TPL_VAR_OP_HH_
#define _OWUI_TPL_VAR_OP_HH_

#include <owui/tpl/base.hh>
#include <owui/tpl/codeOp.hh>
#include <olibs/rto/dynamic.hh>


namespace Owui {
namespace Tpl {  
  

class VarOp : public TextEmittingOp
{
public:
  VarOp(const String& query);

  virtual void exec(Ostream& os, const StaticContext&, DynamicContext& dctx) const;  
  virtual void print(Ostream& os, const String& prefix = "") const;
  virtual TextEmittingOp* clone();

  String query() const {return m_query;}
  
private:
  String m_query;
};

} // namespace Tpl
} // namespace Owui

#endif // _OWUI_TPL_VAR_OP_HH_

