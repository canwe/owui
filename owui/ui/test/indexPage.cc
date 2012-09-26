#include "indexPage.hh"
#include <owui/ui/widgetCatalog.hh>
#include <olibs/rto/meta.hh>
#include <olibs/time/dateTime.hh>
#include <olibs/base/factory.hh>


namespace MyApp {

const char* IndexPage::m_className = "/index";

void myTest_indexPage_registerWidget()
{
  Ui::WidgetCatalog::instance()->regInfo
  (
    new Tpl::TagInfo
    (
      IndexPage::m_className,
      0,
      & IndexPageData::staticMeta()
    )
  );
  
  Factory::instance()->reg(IndexPage::m_className, IndexPage::build);
}

void IndexPage::onInitRequest()
{
  IndexPageData& data = tplDataCast<IndexPageData> ();
  
  data.setGreeting("Greeting from page controller!");
  data.setNow(Time::DateTime::current());
  data.setClockColor("red");
  
  data.setName("Ivan");
  data.setSecondName("Petrov");
  
  data.setLastVisit(request().cookie("owui_lastVisit", false));
  
  
  //m_listOfNames.give(new Olibs::Rto::ListOfTypedDynamic<FullName>());
  Olibs::Rto::ListOfTypedDynamic<FullName>* list = new Olibs::Rto::ListOfTypedDynamic<FullName>();
  {
    FullName* element = new FullName();
    element->setFirsName("Juriy");
    element->setSecondName("Gagarin");
    list->addElement(element);
  }
  {
    FullName* element = new FullName();
    element->setFirsName("Konstantin");
    element->setSecondName("Feoktistov");
    list->addElement(element);
  }  
  {
    FullName* element = new FullName();
    element->setFirsName("Valentina");
    element->setSecondName("Tereshkova");
    list->addElement(element);
  }    
  data.setNames(list);


  setCookie();
}

void IndexPage::onSubmit()
{
  IndexPageData& data = tplDataCast<IndexPageData> ();
    
  data.setName(request().param("name") + "_aa");
  data.setSecondName(request().param("secondName") + "_bb");    
}

void IndexPage::setCookie()
{
  using namespace Time;
  
  response().setCookie(Cookie("owui_lastVisit", DateTime::current().asStr(), DateTime::current() + Interval(1, 0, 0)));

  Cookie c2;
  c2.m_name ="owui_test2";
  c2.m_value = Time::DateTime::current().asStr();
  c2.m_expire = DateTime::current() + Interval(1, 0, 0);
//  c2.m_domain = "yandex.ru";
//  c2.m_path = "/account";
  c2.m_secure = true;
  c2.m_httpOnly = true;
  response().setCookie(c2);
}


} // namespace MyApp

