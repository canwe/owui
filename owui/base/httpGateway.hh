#ifndef _OWUI_BASE_SERVLET_HTTP_GATEWAY_HH_
#define _OWUI_BASE_SERVLET_HTTP_GATEWAY_HH_

#include <owui/base/requestContext.hh>


namespace Owui {
using namespace Olibs;
  
class ServletServer;


class HttpGateway
{
  ServletServer& m_servletServer;
  
public:
  HttpGateway(ServletServer& servletServer);
  virtual ~HttpGateway() {}
  
  virtual void run();
  
protected:
  virtual RequestContext* acceptRequest() = 0;
};



} // namespace Owui

#endif // _OWUI_BASE_SERVLET_HTTP_GATEWAY_HH_

