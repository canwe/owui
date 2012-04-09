#include <owui/fcgi/fcgiGateway.hh>
#include <owui/ui/lib.hh>
#include <owui/ui/dispatcherServlet.hh>
#include <owui/base/servletServer.hh>
#include <owui/tpl/templateManager.hh>
#include <owui/ui/widgetCatalog.hh>
#include <fstream>


using namespace Owui;
using namespace Olibs;


namespace MyApp {
extern void myTest_indexPage_registerWidget();
extern void myTest_clockWidget_registerWidget();
} // MyApp


void test()
{
  OLIBS_DEBOUT("register widgets...\n");
  MyApp::myTest_indexPage_registerWidget();  
  MyApp::myTest_clockWidget_registerWidget();  
  
  OLIBS_DEBOUT("configure template manager...\n");
  Tpl::TemplateManager::instance()->addSourceDir("templates", "/");
  Tpl::TemplateManager::instance()->rescan(Owui::Ui::WidgetCatalog::instance());
    
  OLIBS_DEBOUT("staring fcgi daemon...\n");

  ServletServer servletServer;
  servletServer.add(new Ui::DispatcherServlet);
  
  Fcgi::FcgiGateway gateway(servletServer, ":9000", 100);
  gateway.run();
}

static Ofstream debugLog("debug.log");

void myDebugMsgFunc(const String& text, const String& title)
{
  debugLog << "\n" << title << ": " << text << "\n";
  debugLog.flush();
}

int main ()
{
  try
  {
    LibLoader<Ui::Lib> uiLib;
    test();
  }
  catch(const std::exception& e)
  {
    OLIBS_DEBOUT(String("ex: ") + e.what());
  }
  
  return 0;
}

