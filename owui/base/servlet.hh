#ifndef _OWUI_BASE_SERVLET_HH_
#define _OWUI_BASE_SERVLET_HH_

#include <owui/base/base.hh>

namespace Owui {

class RequestContext;


class Servlet
{
public:
  virtual void service(RequestContext& requestContext) = 0;
};


} // namespace Owui

#endif // _OWUI_BASE_SERVLET_HH_

