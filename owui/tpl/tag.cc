#include <owui/tpl/tag.hh>


namespace Owui {
namespace Tpl {


TagLock::TagLock(TagAllocator* allocator, const String& tagName)
{
  m_tag = 0; // for check after exeption
  
  m_allocator = allocator;
  m_tag       = allocator->allocTag(tagName);

  OLIBS_ASSERT(!empty())
}

TagLock::~TagLock()
{
  if(!empty())
    m_allocator->freeTag(m_tag);
}

TagContext::TagContext(const Rto::Dynamic* params, const Code::Commands* childCommands, DynamicContext* dctx) :
  m_params(params), 
  m_childCommands(childCommands), 
  m_dctx(dctx)
{  
  OLIBS_ASSERT(m_params != 0);
  OLIBS_ASSERT(m_childCommands != 0);
  OLIBS_ASSERT(m_dctx != 0);
}

TagContext::TagContext(const TagContext& rhs) : 
  m_params(rhs.m_params), 
  m_childCommands(rhs.m_childCommands), 
  m_dctx(rhs.m_dctx)
{
  OLIBS_ASSERT(m_params != 0);
  OLIBS_ASSERT(m_childCommands != 0);
  OLIBS_ASSERT(m_dctx != 0);
}

TagContext& TagContext::operator= (const TagContext& rhs)
{
  OLIBS_ASSERT(rhs.m_params != 0);
  OLIBS_ASSERT(rhs.m_childCommands != 0);
  OLIBS_ASSERT(rhs.m_dctx != 0);

  if(&rhs == this)
    return *this;
  
  m_params = rhs.m_params;
  m_childCommands = rhs.m_childCommands;
  m_dctx = rhs.m_dctx;
  
  return *this;  
}

   
} // namespace Tpl
} // namespace Owui  

