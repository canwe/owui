#include "loopWidget.hh"
#include <owui/ui/widgetCatalog.hh>
#include <olibs/rto/meta.hh>
#include <olibs/base/factory.hh>
#include <olibs/time/dateTime.hh>
#include <olibs/rto/dynamic.hh>
#include <olibs/rto/typesInfo.hh>
#include <olibs/base/types.hh>
#include <olibs/rto/typesInfo.hh>
#include <olibs/rto/dynamic.hh>
#include <owui/tpl/dynamicContext.hh>


namespace MyApp {

const char* LoopWidget::m_className = "/myapp/loopWidget";

void myTest_loopWidget_registerWidget()
{
  Olibs::Rto::HiMeta* meta = new Olibs::Rto::HiMeta();
  meta->addField(LoopWidget::fid_list, "list", new Olibs::Rto::DynamicListOfDynamic());
  
  meta->addField(LoopWidget::fid_local, "i", new Olibs::Rto::DynamicReference());
  
  Ui::WidgetCatalog::instance()->regInfo
  (
    new Tpl::TagInfo
    (
      LoopWidget::m_className,
      meta, 
      0
    )
  );
  
  Factory::instance()->reg(LoopWidget::m_className, LoopWidget::build);
}

void LoopWidget::beginDrawing(Ostream& os, const Tpl::TagContext& context)
{
}

void LoopWidget::endDrawing(Ostream& os, const Tpl::TagContext& context)
{
}

void LoopWidget::drawBody(Ostream& os, const Tpl::TagContext& context)
{
  OLIBS_ASSERT(context.m_params->at<Olibs::Rto::ListOfDynamic*>(fid_list) != 0);
  

  Tpl::TagContext localContext;
  localContext.m_childCommands = context.m_childCommands;
  localContext.m_dctx = context.m_dctx;

  Olibs::Optr<Olibs::Rto::Dynamic> localParamsDynamic(new Rto::Dynamic(context.m_params->meta()));
  
  localParamsDynamic->at<Olibs::Rto::ListOfDynamic*>(fid_list) = context.m_params->at<Olibs::Rto::ListOfDynamic*>(fid_list);
  Olibs::Rto::ListOfDynamic& list = *localParamsDynamic->at<Olibs::Rto::ListOfDynamic*>(fid_list);

  localContext.m_params = localParamsDynamic;
  
  for(Olibs::Rto::ListOfDynamic::Iterator it = list.begin(); it != list.end(); ++it)
  {
    localParamsDynamic->at<Olibs::Rto::Dynamic*>(fid_local) = *it;    
    Widget::drawBody(os, localContext);
  }
}


} // namespace MyApp


