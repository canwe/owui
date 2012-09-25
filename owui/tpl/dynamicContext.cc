#include <olibs/base/assert.hh>
#include <owui/tpl/dynamicContext.hh>


namespace Owui {
namespace Tpl {


DynamicContext::DynamicContext()
{}  

const Olibs::Rto::Dynamic* DynamicContext::data() const 
{
  OLIBS_ASSERT(m_contexts.size() != 0);
  const Rto::Dynamic* data = m_contexts.top();
  OLIBS_ASSERT(data != 0);
  return data;
}  
  
void DynamicContext::push(const Rto::Dynamic* data)
{
  OLIBS_ASSERT(data != 0);
  m_contexts.push(data);  
}

void DynamicContext::pop()
{
  OLIBS_ASSERT(m_contexts.size() > 0);
  m_contexts.pop();
  OLIBS_ASSERT(m_contexts.size() > 0);
}


} // namespace Tpl
} // namespace Owui
