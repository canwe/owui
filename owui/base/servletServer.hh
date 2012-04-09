#ifndef _OWUI_BASE_SERVLET_SERVER_HH_
#define _OWUI_BASE_SERVLET_SERVER_HH_

#include <owui/base/servlet.hh>
#include <olibs/base/optr.hh>

#include <vector>

namespace Owui {
using namespace Olibs;
  

class ServletServer
{
public:  
  struct ServletInf
  {
    Optr<Servlet> m_servlet;
    String        m_uriPrefix;
  };
  
  typedef std::vector<ServletInf*> Servlets;

private:  
  Servlets m_servlets;

public:
  ~ServletServer();
  
  void add(Servlet* servlet, const String uriPrefix = "");
  
  Servlet& find(const String& uri) const;
  const Servlets& servlets() const {return m_servlets;} 
  
  void service(RequestContext* reqCtx);
};


} // namespace Owui

#endif // _OWUI_BASE_SERVLET_SERVER_HH_

