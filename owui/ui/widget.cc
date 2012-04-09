#include <owui/ui/widget.hh>
#include <owui/ui/widgetCatalog.hh>


namespace Owui {
namespace Ui {

  
Widget::Widget()
{
  m_isInited = false;
}

//! place for widget object initialization   
void Widget::initWidget()
{
  if(m_isInited)
    return;
  
  const Owui::Tpl::TagInfo& tagInfo = WidgetCatalog::instance()->findInfo(className());  
  m_tplData.give(new Rto::Dynamic(* tagInfo.m_tplDataMeta));

  m_isInited = true;
  onInitWidget();
}
  
// It calls from DispatcherServlet. Once at the start of http request....
void Widget::initRequest(Owui::RequestContext* requestContext)
{
  m_requestContext = requestContext;
  
  onInitRequest();
}

void Widget::submit()
{
  onSubmit();
}


} // namespace Ui
} // namespace Owui

