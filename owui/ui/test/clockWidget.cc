#include "clockWidget.hh"
#include "_clockWidgetParams.rto.hh"
#include <owui/ui/widgetCatalog.hh>

#include <olibs/rto/meta.hh>
#include <olibs/base/factory.hh>
#include <olibs/time/dateTime.hh>


namespace MyApp {

const char* ClockWidget::m_className = "/myapp/clockWidget";

void myTest_clockWidget_registerWidget()
{
  Ui::WidgetCatalog::instance()->regInfo
  (
    new Tpl::TagInfo
    (
      ClockWidget::m_className,
      & ClockWidgetParams::staticMeta(), 
      0
    )
  );
  
  Factory::instance()->reg(ClockWidget::m_className, ClockWidget::build);
}

void ClockWidget::draw(Ostream& os, const Tpl::TagContext& ctx)
{
  const ClockWidgetParams* const  params = static_cast<const ClockWidgetParams* const>(ctx.m_params);
  
  Time::DateTime time = Time::DateTime::current(); 
  
  os
    << "<font color=\"" << params->getColor() << "\">\n"
    << "<span>\n"
    << "  <em>" << time << "</em>\n"
  ;
  
//  const Olibs::Rto::Dynamic& params = *tagCtx.m_params;
// \todo: Тут вывести все params из dynamic
  
  os << "</font>\n";
  os << "</span>\n";

  
  
}

} // namespace MyApp

