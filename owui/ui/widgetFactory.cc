#if 0

#include <owui/ui/widgetFactory.hh>
#include <olibs/base/assert.hh>


namespace Owui {
namespace Ui {


Widget* WidgetFactory::create(const Olibs::String& tagName)
{
  Olibs::Object* object = m_pool->alloc(tagName);
  
  OLIBS_ASSERT(object != 0);
  OLIBS_ASSERT(dynamic_cast<Widget*>(object) != 0);
  
  return static_cast<Widget*>(object);
}

void WidgetFactory::destroy(Owui::Tpl::Template* object)
{
  OLIBS_ASSERT(object != 0);
  OLIBS_ASSERT(dynamic_cast<Widget*>(object) != 0);
  
  m_pool->free(object);
}



WidgetFactory::WidgetFactory() :
  m_pool(new WidgetPool())
{
  init();
}

void WidgetFactory::registarateWidget(const Olibs::String& objectName, Olibs::Tools::ObjectFactoryCreator::BuildFunc buildFunc)
{
  m_pool->addCreator(objectName, buildFunc);
  
  Olibs::Object* object = buildFunc();
  OLIBS_ASSERT(object != 0);
  OLIBS_ASSERT(dynamic_cast<Owui::Tpl::Template*>(object) != 0);
  
  TagManager::addTemplate(static_cast<Owui::Tpl::Template*>(object));
}

void WidgetFactory::init()
{
  /*
  void addCreator(const Olibs::String& objectName, Olibs::Tools::ObjectFactoryCreator::BuildFunc buildFunc);
  m_pool->addCreator();
  */
}



} // namespace Ui
} // namespace Owui

#endif

