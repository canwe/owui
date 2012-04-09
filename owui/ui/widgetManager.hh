#ifndef _OWUI_UI_WIDJET_MANAGER_HH_
#define _OWUI_UI_WIDJET_MANAGER_HH_

#include <owui/ui/widget.hh>
#include <owui/tpl/tag.hh>
#include <olibs/base/onlyOne.hh>


namespace Owui {
namespace Ui {

  
class WidgetManager: public Olibs::OnlyOne<WidgetManager>, public Tpl::TagAllocator
{
public:
  WidgetManager();
  
  virtual Tpl::Tag* allocTag(const String& tagName);
  virtual void freeTag(Tpl::Tag* tag);
};
  

class WidgetLock: public Tpl::TagLock
{
public:
  WidgetLock(Tpl::TagAllocator* allocator, const String& tagName):
    TagLock(allocator, tagName) {}  
  
  Widget* operator-> () const {return (Widget*)TagLock::operator->();}
};


} // namespace Ui
} // namespace Owui

#endif // _OWUI_UI_WIDJET_MANAGER_HH_

