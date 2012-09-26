#ifndef _MYAPP_LOOP_WIDGET_HH_
#define _MYAPP_LOOP_WIDGET_HH_

#include <owui/ui/widget.hh>


namespace Owui { namespace Tpl {
class TagContext;
}}


namespace MyApp {

using namespace Owui;  
  
class LoopWidget: public Ui::Widget
{
public:
  enum {fid_list, fid_variable};
  static const char* m_className;
  
  virtual const char* className() const {return m_className;}  

  static Object* build() {return new LoopWidget();}
  
private:  
  virtual void beginDrawing(Ostream& os, const Tpl::TagContext& context);
  virtual void endDrawing(Ostream& os, const Tpl::TagContext& context);    
  virtual void drawBody(Ostream& os, const Tpl::TagContext& context);
  
  
};

} // namespace MyApp

#endif // _MYAPP_CLOCK_WIDGET_HH_