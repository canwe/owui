#ifndef _OWUI_UI_TPL_WIDJET_HH_
#define _OWUI_UI_TPL_WIDJET_HH_

#include <owui/widget/base.hh>
#include <owui/tpl/code.hh>


namespace Owui {
namespace Ui {

/*
*/
class TplWidget : public Widget
{
public:
  virtual void draw(Ostream& os, const Context& context);  
  
};


} // namespace Ui
} // namespace Owui

#endif // _OWUI_UI_TPL_WIDJET_HH_

