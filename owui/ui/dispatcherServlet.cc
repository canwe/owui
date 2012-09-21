#include <owui/ui/dispatcherServlet.hh>
#include <owui/base/httpRequest.hh>
#include <owui/base/httpResponse.hh>
#include <owui/base/requestContext.hh>
#include <owui/ui/widgetManager.hh>
#include <owui/tpl/tag.hh>
#include <owui/tpl/templateManager.hh>
#include <owui/tpl/template.hh>
#include <owui/tpl/executor.hh>
#include <owui/tpl/dynamicContext.hh>

#include <olibs/base/debug.hh>
#include <olibs/str/ut.hh>


namespace Owui {
namespace Ui {

  
void DispatcherServlet::service(RequestContext& reqCtx)
{
  HttpRequest& request = reqCtx.request();

OstringStream debOs;  
request.printEnv(debOs);
OLIBS_DEBOUT(debOs.str());

//  OLIBS_DEBOUT("request content-type: " + request.env("CONTENT_TYPE"));
    
  String pageName = Str::toLower(request.env("PATH_INFO"));

  if(pageName == "/")
     pageName = "/index";    

  try
  {
    WidgetLock wgtLock(WidgetManager::instance(), pageName);
    if(wgtLock.empty())
      OLIBS_DEBOUT("page widget not found: " + pageName);

    const Tpl::TemplateManager* tplMgr = Tpl::TemplateManager::instance();
    const Tpl::Template* tpl = tplMgr->findTemplate(pageName);

    if(tpl != 0)
    {
      OLIBS_DEBOUT("found template: " + tpl->sourceFname());
      
      wgtLock->initWidget();
      wgtLock->initRequest(&reqCtx);
      
      if(request.testEnv("CONTENT_TYPE", "application/x-www-form-urlencoded"))
        wgtLock->submit();
      
      Tpl::Executor executor(tpl->code());
      
      Tpl::DynamicContext dctx(wgtLock->tplData());
      
      executor.exec(dctx, reqCtx.response().os());
    }
    
    if(wgtLock.empty() && tpl == 0)
      pageNotFound(reqCtx, pageName);    
  }
  catch(const std::exception& e)
  {
    OLIBS_DEBOUT(String("owui ex: ") + e.what());
    reqCtx.response().os() << "owui ex: " << e.what() << "<p>";
  }  
}

// \todo: Сделать возможность использовать обычный wut template (через redirect на другую страницу)
// \todo: а простым текстом выдавать только если нет такого шаблона
void DispatcherServlet::pageNotFound(RequestContext& reqCtx, const String& pageName)
{
  reqCtx.response().os() << "<h2>page not found: " << pageName << "</h2>";
}


} // namespace Ui
} // namespace Owui

