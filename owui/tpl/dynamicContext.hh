#ifndef _OWUI_TPL_CODE_CONTEXT_HH_
#define _OWUI_TPL_CODE_CONTEXT_HH_

#include <owui/tpl/base.hh>
#include <olibs/base/optr.hh>
#include <olibs/rto/dynamic.hh>

namespace Owui {
namespace Tpl {


class DynamicContext
{
public:  
  DynamicContext(Rto::Dynamic* data):
    m_data(data)
  {}

  const Olibs::Rto::Dynamic* data() const {return m_data;}
  
private:
  Rto::Dynamic* m_data;
};


} // namespace Tpl
} // namespace Owui

#endif // _OWUI_TPL_CODE_CONTEXT_HH_

