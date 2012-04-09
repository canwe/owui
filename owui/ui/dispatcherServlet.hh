#ifndef _OWUI_UI_DISPATCHER_SERVLET_HH_
#define _OWUI_UI_DISPATCHER_SERVLET_HH_

#include <owui/ui/base.hh>
#include <owui/base/servlet.hh>


namespace Owui {
namespace Ui {

  
class DispatcherServlet: public Servlet
{
public:  
  virtual void service(RequestContext& reqCtx);
  
  static String widgetNameByUriPath(const String& path);
  
protected:
  virtual void pageNotFound(RequestContext& reqCtx, const String& pageName);
};
  

} // namespace Ui
} // namespace Owui

#endif // _OWUI_UI_DISPATCHER_SERVLET_HH_

