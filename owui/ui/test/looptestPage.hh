#ifndef _LOOPTEST_INDEX_PAGE_HH_
#define _LOOPTEST_INDEX_PAGE_HH_

#include <owui/ui/widget.hh>
#include "_looptestPageData.rto.hh"

namespace Owui { namespace Tpl {
class TagContext;
}}




namespace MyApp {

using namespace Owui;  
  
class LoopTestPage: public Ui::Widget
{
public: 
  static const char* m_className;

  virtual const char* className() const {return m_className;}  
  static Object* build() {return new LoopTestPage;}
  
protected:  
  virtual void onInitRequest();  
  Olibs::Optr<Olibs::Rto::ListOfTypedDynamic<FullName> > m_fullNamesList;
  Olibs::Optr<Olibs::Rto::ListOfTypedDynamic<IntPair> > m_intPairsList;
  
};

} // namespace MyApp

#endif // _LOOPTEST_INDEX_PAGE_HH_

