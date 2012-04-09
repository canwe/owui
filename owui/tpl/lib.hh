#ifndef _OWUI_TPL_LIB_HH_
#define _OWUI_TPL_LIB_HH_

#include <owui/base/lib.hh>
#include <owui/tpl/templateManager.hh>


namespace Owui {
namespace Tpl {


//////////////////////
// Lib
class Lib: public LibTempl<Lib>
{
   LibLoader<Owui::Lib> m_baseLoader;
   TemplateManager      m_templateManager;

public:
  Lib();
  ~Lib() {}
};


} // namespace Tpl
} // namespace Owui

#endif // _OWUI_TPL_LIB_HH_

