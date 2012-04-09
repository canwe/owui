#ifndef _OWUI_BASE_REQUEST_CONTEXT_HH_
#define _OWUI_BASE_REQUEST_CONTEXT_HH_

#include <owui/base/httpRequest.hh>
#include <owui/base/httpResponse.hh>


namespace Owui {
using namespace Olibs;
  

class RequestContext
{
  Optr<HttpRequest>  m_request;
  Optr<HttpResponse> m_response;
  
public:
  RequestContext(HttpRequest* req, HttpResponse* resp)
    {m_request.give(req); m_response.give(resp);}

  HttpRequest& request()    {return *m_request;}
  HttpResponse& response()  {return *m_response;}
};


} // namespace Owui

#endif // _OWUI_BASE_REQUEST_CONTEXT_HH_

