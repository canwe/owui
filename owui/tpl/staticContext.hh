#ifndef _OWUI_TPL_STATIC_CONTEXT_HH_
#define _OWUI_TPL_STATIC_CONTEXT_HH_

#include <owui/tpl/base.hh>
#include <olibs/base/optr.hh>

namespace Owui {
namespace Tpl {

  
class TagCatalog;
class TagAllocator;


class StaticContext
{
public:  
  StaticContext(const TagCatalog& tagCatalog, TagAllocator* tagAllocator):
    m_tagCatalog(tagCatalog),
    m_tagAllocator(tagAllocator)
  {}
  
  const TagCatalog& tagCatalog() const   {return m_tagCatalog;}
  TagAllocator*     tagAllocator() const {return m_tagAllocator;} 
  
private:
  const TagCatalog&                m_tagCatalog;
  TagAllocator*                    m_tagAllocator; 
};


} // namespace Tpl
} // namespace Owui

#endif // _OWUI_TPL_STATIC_CONTEXT_HH_

