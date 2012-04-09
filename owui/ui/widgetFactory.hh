#ifndef _OWUI_UI_WIDJET_FACTORY_HH_
#define _OWUI_UI_WIDJET_FACTORY_HH_

#include <owui/ui/widget.hh>
#include <owui/ui/widgetPool.hh>
#include <olibs/base/onlyOne.hh>
#include <owui/tpl/templateManager.hh>
#include <olibs/base/optr.hh>


namespace Owui {
namespace Ui {

 

class WidgetFactory : public Owui::Tpl::TagManager, public Olibs::OnlyOne<WidgetFactory>
{
public:
  WidgetFactory();
  virtual ~WidgetFactory(){};
  virtual Widget* create(const Olibs::String& tagName);
  virtual void destroy(Owui::Tpl::Template* object);
  
  void registarateWidget(const Olibs::String& objectName, Olibs::Tools::ObjectFactoryCreator::BuildFunc buildFunc);
  
  
private:
  void init();  
  
  
private:
  Olibs::Optr<WidgetPool> m_pool;
  
};









} // namespace Ui
} // namespace Owui

#endif // _OWUI_UI_WIDJET_MANAGER_HH_

