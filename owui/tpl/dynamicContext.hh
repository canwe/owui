#ifndef _OWUI_TPL_CODE_CONTEXT_HH_
#define _OWUI_TPL_CODE_CONTEXT_HH_

#include <owui/tpl/base.hh>
#include <olibs/base/optr.hh>
#include <olibs/rto/dynamic.hh>
#include <stack>
#include <list>


namespace Owui {
namespace Tpl {


class DynamicContext
{
public:  
  DynamicContext();
  const Olibs::Rto::Dynamic* data() const;
  
  
  void push(const Rto::Dynamic* data);
  void pop();
  
private: 
  std::stack<const Olibs::Rto::Dynamic*, std::list<const Olibs::Rto::Dynamic*> > m_contexts;
};


} // namespace Tpl
} // namespace Owui

#endif // _OWUI_TPL_CODE_CONTEXT_HH_
