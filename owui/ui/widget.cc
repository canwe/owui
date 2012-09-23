#include <owui/ui/widget.hh>
#include <owui/ui/widgetCatalog.hh>
#include <owui/tpl/dynamicContext.hh>
#include <owui/tpl/execOp.hh>

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

void Widget::draw(Ostream& os, const Tpl::TagContext& context) 
{
  beginDrawing(os, context);
  drawChildWidgets(os, context);
  endDrawing(os, context);
}

void Widget::drawChildWidgets(Ostream& os, const Tpl::TagContext& context)
{
  OLIBS_ASSERT(context.m_dctx != 0);
  OLIBS_ASSERT(context.m_childCommands != 0);
  OLIBS_ASSERT(context.m_params != 0);
  

  context.m_dctx->push(context.m_params);
  
  const Tpl::Code::Commands& cmds = *context.m_childCommands;
  typedef Tpl::Code::Commands::const_iterator Cit;

  for(Cit ci = cmds.begin(); ci != cmds.end(); ++ci)
    (*ci)->exec(os, *context.m_dctx);
  
  context.m_dctx->pop();
}


} // namespace Ui
} // namespace Owui

