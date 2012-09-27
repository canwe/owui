#include "looptestPage.hh"
#include <owui/ui/widgetCatalog.hh>
#include <olibs/rto/meta.hh>
#include <olibs/base/factory.hh>


namespace MyApp {


const char* LoopTestPage::m_className = "/looptest";

void myTest_indexPage_registerWidget()
{
  Ui::WidgetCatalog::instance()->regInfo
  (
    new Tpl::TagInfo
    (
      LoopTestPage::m_className,
      0,
      &LoopTestPageData::staticMeta()
    )
  );
  
  Factory::instance()->reg(LoopTestPage::m_className, LoopTestPage::build);
}


void LoopTestPage::onInitRequest()
{
  LoopTestPageData& data = tplDataCast<LoopTestPageData>();
  
  m_fullNamesList.give(new Olibs::Rto::ListOfTypedDynamic<FullName>());
  {
    FullName* element = new FullName();
    element->setFirsName("Juriy");
    element->setSecondName("Gagarin");
    m_fullNamesList->addElement(element);
  }
  {
    FullName* element = new FullName();
    element->setFirsName("Konstantin");
    element->setSecondName("Feoktistov");
    m_fullNamesList->addElement(element);
  }  
  {
    FullName* element = new FullName();
    element->setFirsName("Valentina");
    element->setSecondName("Tereshkova");
    m_fullNamesList->addElement(element);
  }    
  data.setNames(m_fullNamesList.get());

  
  
  m_intPairsList.give(new Olibs::Rto::ListOfTypedDynamic<IntPair>());
  {
    IntPair* element = new IntPair();
    element->setFirst(1);
    element->setSecond(2);
    m_intPairsList->addElement(element);
  } 
  {
    IntPair* element = new IntPair();
    element->setFirst(3);
    element->setSecond(4);
    m_intPairsList->addElement(element);
  } 
  {
    IntPair* element = new IntPair();
    element->setFirst(5);
    element->setSecond(6);
    m_intPairsList->addElement(element);
  } 
  {
    IntPair* element = new IntPair();
    element->setFirst(7);
    element->setSecond(8);
    m_intPairsList->addElement(element);
  } 
  {
    IntPair* element = new IntPair();
    element->setFirst(9);
    element->setSecond(10);
    m_intPairsList->addElement(element);
  } 
  {
    IntPair* element = new IntPair();
    element->setFirst(11);
    element->setSecond(12);
    m_intPairsList->addElement(element);
  }   
  data.setPairs(m_intPairsList.get());
  
  
}


} // namespace MyApp

