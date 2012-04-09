#include <owui/ui/widgetCatalog.hh>
#include <olibs/base/debug.hh>
#include <olibs/str/ut.hh>
#include <algorithm>


namespace Owui {
namespace Ui {


bool TagInfoComparer::operator() (const first_argument_type& x, const second_argument_type& y) const
{
  return (Olibs::Str::compareNoCase(x->m_name, y->m_name) > 0);
}

WidgetCatalog::~WidgetCatalog()
{
  for(TagInfos::iterator it = m_tagInfos.begin(); it != m_tagInfos.end(); ++it)
    delete (*it);
}
  
struct FindByNamePredicate : std::binary_function<Owui::Tpl::TagInfo*, String, bool>
{
  bool operator() (const first_argument_type& structure, const second_argument_type& name) const
  {
    return (Olibs::Str::compareNoCase(structure->m_name, name) == 0);
  }
};
const Owui::Tpl::TagInfo& WidgetCatalog::findInfo(const String& tagName) const
{
  OLIBS_DEBOUT("find wgt: " + tagName);  

  TagInfos::const_iterator it = std::find_if(m_tagInfos.begin(), m_tagInfos.end(), std::bind2nd(FindByNamePredicate(), tagName));
  
  if(it == m_tagInfos.end())
    throw WidgetNotFoundEx(tagName);
  
  return *(*it);
}

void WidgetCatalog::regInfo(Owui::Tpl::TagInfo* tagInfo)
{
OLIBS_DEBOUT("reg wgt: " + tagInfo->m_name);  
  m_tagInfos.insert(tagInfo);
}


} // namespace Ui
} // namespace Owui


