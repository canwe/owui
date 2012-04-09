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

   
} // namespace Tpl
} // namespace Owui  

