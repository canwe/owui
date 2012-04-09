#include <owui/ui/widgetManager.hh>
#include <owui/ui/widget.hh>
#include <olibs/base/factory.hh>
#include <olibs/base/exception.hh>


namespace Owui {
namespace Ui {

  /* \todo
  Простейшая и тупая реализация. Переделать с использованием ObjectCashe
  */

WidgetManager::WidgetManager()
{}

Tpl::Tag* WidgetManager::allocTag(const String& widgetName)
{
  Widget* widget = 0;

  try
  {  
    Object* object = Factory::instance()->createObj(widgetName);
    OLIBS_ASSERT(object != 0);
    widget = dynamic_cast<Widget*>(object);
    OLIBS_ASSERT(widget != 0);
  }
  catch(const Factory::ClassNotFoundEx& e)
  {
    cerr << "ex: " << e.what() << std::endl;
    throw;
  }
  
  return widget;
}

void WidgetManager::freeTag(Tpl::Tag* tag)
{
  OLIBS_ASSERT(tag != 0);
  delete tag;
}

} // namespace Ui
} // namespace Owui

