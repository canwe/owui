#ifndef _OWUI_FCGI_LIB_HH_
#define _OWUI_FCGI_LIB_HH_

#include <owui/base/lib.hh>


namespace Owui {
namespace Fcgi {


//////////////////////
// Lib
class Lib: public LibTempl<Lib>
{
   LibLoader<Owui::Lib> m_baseLoader;

public:
  Lib()  {}
  ~Lib() {}
};


} // namespace Fcgi
} // namespace Owui

#endif // _OWUI_FCGI_LIB_HH_
