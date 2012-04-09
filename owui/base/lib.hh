#ifndef _OWUI_BASE_LIB_HH_
#define _OWUI_BASE_LIB_HH_

#include <owui/base/base.hh>
#include <olibs/rto/lib.hh>


namespace Owui {

using namespace Olibs;
  
//////////////////////
// Lib
class Lib: public LibTempl<Lib>
{
  LibLoader<Olibs::Rto::Lib> m_baseLoader;

public:
  Lib()  {}
  ~Lib() {}
};


} // namespace Owui

#endif // _OWUI_BASE_LIB_HH_

