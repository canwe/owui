#ifndef _TEST_INDEX_PAGE_HH_
#define _TEST_INDEX_PAGE_HH_

#include <owui/ui/widget.hh>
#include "_IndexPageData.rto.hh"

namespace Owui { namespace Tpl {
class TagContext;
}}

class IndexPageData;


namespace MyApp {

using namespace Owui;  
  
class IndexPage: public Ui::Widget
{
public:
  static const char* m_className;
  
  virtual const char* className() const {return m_className;}  

  static Object* build() {return new IndexPage;}
  
protected:  
  virtual void onInitRequest();  
  virtual void onSubmit();  
  
private:
  void setCookie();
  Olibs::Optr<Olibs::Rto::ListOfTypedDynamic<FullName> > m_listOfNames;
  
};

} // namespace MyApp

#endif // _TEST_INDEX_PAGE_HH_

