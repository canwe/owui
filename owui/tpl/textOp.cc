#include <owui/tpl/textOp.hh>
#include <olibs/base/debug.hh>


namespace Owui {
namespace Tpl {

void TextOp::exec(Ostream& os, DynamicContext& dctx) const
{
  OLIBS_DEBOUT("exec txt: " + m_data);
  os << m_data;
}

void TextOp::print(Ostream& os, const String& prefix) const
{
  os << prefix << "TEXT:\n" << m_data << "\n\n";
}

TextEmittingOp* TextOp::clone()
{
  return new TextOp(*this);
}

} // namespace Tpl
} // namespace Owui

