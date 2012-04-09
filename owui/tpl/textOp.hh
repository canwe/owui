#ifndef _OWUI_TPL_TEXT_OP_HH_
#define _OWUI_TPL_TEXT_OP_HH_

#include <owui/tpl/base.hh>
#include <owui/tpl/codeOp.hh>


namespace Owui {
namespace Tpl {  
  

class TextOp : public TextEmittingOp
{
  String m_data;

public:
  TextOp(const String& data): m_data(data) {}

public:
  const String& data() const   {return m_data; }
  
  virtual void exec(Ostream& os, const StaticContext& sctx, DynamicContext& dctx) const;  
  virtual void print(Ostream& os, const String& prefix = "") const;
  virtual TextEmittingOp* clone();
};

} // namespace Tpl
} // namespace Owui

#endif // _OWUI_TPL_TEXT_OP_HH_

