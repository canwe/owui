#include <owui/base/httpGateway.hh>
#include <owui/base/servletServer.hh>


namespace Owui {
  
  
HttpGateway::HttpGateway(ServletServer& servletServer):
m_servletServer(servletServer)
{
}

void HttpGateway::run()
{
  OLIBS_DEBOUT("HttpGateway::run()\n");
  
  for(;;)
  {
    RequestContext* reqCtx = acceptRequest();
    if(reqCtx == 0)
      break;
    
    m_servletServer.service(reqCtx);
  }
}


} // namespace Owui

