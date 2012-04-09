#include <owui/ui/lib.hh>
#include <owui/tpl/templateManager.hh>
#include <owui/tpl/staticContext.hh>

namespace Owui {
namespace Ui {

  
Lib::Lib()
{
  m_staticContext.give(new Tpl::StaticContext(m_widgetCatalog, &m_widgetManager));
  Tpl::TemplateManager::instance()->setCodeCtx(m_staticContext.get());
}
  
} // namespace Ui
} // namespace Owui