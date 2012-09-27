#include "loopWidget.hh"
#include <owui/ui/widgetCatalog.hh>
#include <olibs/base/factory.hh>
#include <olibs/rto/typesInfo.hh>
#include <olibs/base/types.hh>


namespace MyApp {
 
const char* LoopWidget::m_className = "/myapp/loopWidget";

void myTest_loopWidget_registerWidget()
{
  Olibs::Rto::HiMeta* meta = new Olibs::Rto::HiMeta();
  meta->addField(LoopWidget::fid_list, "list", new Olibs::Rto::DynamicListOfDynamic());
  meta->addField(LoopWidget::fid_variable, "i", new Olibs::Rto::DynamicReference());
  
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
  OLIBS_ASSERT(context.m_params->at<Rto::ListOfDynamic*>(fid_list) != 0);
  
  Optr<Olibs::Rto::Dynamic> localParamsDynamic(Rto::Dynamic::clone(*context.m_params));
  
  Rto::ListOfDynamic& list = *localParamsDynamic->at<Rto::ListOfDynamic*>(fid_list);

  Tpl::TagContext localContext(context);
  localContext.m_params = localParamsDynamic;

  for(Rto::ListOfDynamic::Iterator it = list.begin(); it != list.end(); ++it)
  {
    OLIBS_ASSERT(*it != 0);
    localParamsDynamic->at<Rto::Dynamic*>(fid_variable) = *it;
    Widget::drawBody(os, localContext);
    localParamsDynamic->at<Rto::Dynamic*>(fid_variable) = 0;
  }

}


} // namespace MyApp


