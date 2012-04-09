#include <owui/base/servletServer.hh>
#include <owui/base/requestContext.hh>
#include <olibs/base/exception.hh>


namespace Owui {


ServletServer::~ServletServer()
{
  for(Servlets::iterator it = m_servlets.begin(); it != m_servlets.end(); ++it)
    delete *it;
}
  
void ServletServer::add(Servlet* servlet, const String uriPrefix)
{
  ServletInf* inf = new ServletInf;
  inf->m_servlet.give(servlet);
  inf->m_uriPrefix = uriPrefix;
  
  m_servlets.push_back(inf);
}
  
Servlet& ServletServer::find(const String& uri) const
{
  Servlet* defaultServlet = 0;
  
  for(Servlets::const_iterator it = m_servlets.begin(); it != m_servlets.end(); ++it)
  {
    ServletInf* inf = *it;
    
    if(inf->m_uriPrefix.empty())
      defaultServlet = inf->m_servlet.get();
    
    else if(uri.substr(inf->m_uriPrefix.length()) ==  inf->m_uriPrefix)
      return *inf->m_servlet;
  }
  
  if(defaultServlet != 0)
    return *defaultServlet;

  throw StrEx("Cannot find servlet");
}

void ServletServer::service(RequestContext* aReqCtx)
{
  Optr<RequestContext> reqCtx(aReqCtx);
  
  find(reqCtx->request().uri()).service(*reqCtx);
  reqCtx->response().flushHeaders();    
}


} // namespace Owui

