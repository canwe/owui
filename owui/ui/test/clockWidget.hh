#ifndef _MYAPP_CLOCK_WIDGET_HH_
#define _MYAPP_CLOCK_WIDGET_HH_

#include <owui/ui/widget.hh>


namespace Owui { namespace Tpl {
class TagContext;
}}


namespace MyApp {

using namespace Owui;  
  
class ClockWidget: public Ui::Widget
{
public:
  static const char* m_className;
  
  virtual const char* className() const {return m_className;}  
  virtual void draw(Ostream& os, const Tpl::TagContext& context);

  static Object* build() {return new ClockWidget();}
};

} // namespace MyApp

#endif // _MYAPP_CLOCK_WIDGET_HH_

