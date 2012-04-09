#ifndef _OWUI_UI_WIDJET_CATALOG_HH_
#define _OWUI_UI_WIDJET_CATALOG_HH_

#include <owui/ui/base.hh>
#include <owui/tpl/tag.hh>
#include <olibs/base/exception.hh>
#include <olibs/base/onlyOne.hh>

#include <map>
#include <set>
#include <functional>


namespace Owui {
namespace Ui {

class Widget;

struct TagInfoComparer : std::binary_function <Owui::Tpl::TagInfo*, Owui::Tpl::TagInfo*, bool>
{
  bool operator() (const first_argument_type& x, const second_argument_type& y) const;
};


class WidgetCatalog : public Owui::Tpl::TagCatalog, public Olibs::OnlyOne<WidgetCatalog>
{
public:
  typedef std::set<Owui::Tpl::TagInfo*> TagInfos;
  
  class WidgetNotFoundEx: public StrEx
  {
  public:
    WidgetNotFoundEx(const String& name) : StrEx(String("Widget '") + name + "' not found") {} 
  };
  
  ~WidgetCatalog();
  
  virtual const Owui::Tpl::TagInfo& findInfo(const String& tagName) const;
  void regInfo(Owui::Tpl::TagInfo* tagInfo);
  
private:
  TagInfos m_tagInfos;
};


} // namespace Ui
} // namespace Owui

#endif // _OWUI_UI_WIDJET_CATALOG_HH_

