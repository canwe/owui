#ifndef _OWUI_UI_WIDJET_HH_
#define _OWUI_UI_WIDJET_HH_

#include <olibs/base/optr.hh>
#include <olibs/rto/dynamic.hh>
#include <olibs/base/object.hh>
#include <owui/tpl/tag.hh>
#include <owui/base/requestContext.hh>

namespace Owui {
  
namespace Tpl {
  class TagContext;
}
  
  
namespace Ui {

/*
Рисует (выдает html) Widget. Для паралельной обработки запросов создается много объектов.
Они не имеют состояния между запросами, один объект может обрабатывать запросы от различных http клиентов.
Тем не менее в процессе обработки одного http запроса один объект целиком отдается под обработку запроса.
*/
class Widget : public Owui::Tpl::Tag
{
public:
  /** вызывается
  * 1. При http запросе данного widget как страницы.
  * 2. Из template, который в свою очередь может вызываться либо из http, либо из другого template
  context - все данные связанные с обработкой запроса
  */
  virtual void draw(Ostream& os, const Tpl::TagContext& context);

  Rto::Dynamic* tplData()                 {return m_tplData.get();}
  template <class T> T& tplDataCast()     {return *((T*)m_tplData.get());}

// Must be called only from dispatcherServlet:  
  void initWidget();
  void initRequest(Owui::RequestContext* requestContext);
  virtual void submit();  
  
protected:
  Widget();
  
  const Owui::HttpRequest&  request() const  {return m_requestContext->request();}
  Owui::HttpResponse& response()             {return m_requestContext->response();}
  
  virtual void onInitWidget()  {}
  virtual void onInitRequest() {};  
  virtual void onSubmit()      {};  
  
  virtual void beginDrawing(Ostream& os, const Tpl::TagContext& context){};
  virtual void drawBody(Ostream& os, const Tpl::TagContext& context);
  virtual void endDrawing(Ostream& os, const Tpl::TagContext& context){};  
  
  
private:
  RequestContext*           m_requestContext;
  Optr<Rto::Dynamic>        m_tplData;
  bool                      m_isInited;
};


} // namespace Ui
} // namespace Owui

#endif // _OWUI_UI_WIDJET_HH_

