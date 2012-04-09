#ifndef _OWUI_UI_LIB_HH_
#define _OWUI_UI_LIB_HH_

#include <owui/fcgi/lib.hh>
#include <owui/tpl/lib.hh>
#include <owui/tpl/staticContext.hh>
#include <owui/ui/widgetManager.hh>
#include <owui/ui/widgetCatalog.hh>

#include <olibs/rto/lib.hh>
#include <olibs/base/optr.hh>


namespace Owui {
namespace Ui {


//////////////////////
// Lib
class Lib: public LibTempl<Lib>
{
  LibLoader<Olibs::Rto::Lib> m_rtoLoader;
  LibLoader<Owui::Fcgi::Lib> m_fcgiLoader;
  LibLoader<Owui::Tpl::Lib>  m_tplLoader;
  
  WidgetCatalog             m_widgetCatalog;
  WidgetManager             m_widgetManager;
  Optr<Tpl::StaticContext>  m_staticContext;

public:
  Lib();
  ~Lib() {}
};


} // namespace Ui
} // namespace Owui

#endif // _OWUI_UI_LIB_HH_

