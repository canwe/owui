#ifndef _OWUI_FCGI_GATEWAY_HH_
#define _OWUI_FCGI_GATEWAY_HH_

#include <owui/fcgi/base.hh>
#include <owui/base/httpGateway.hh>
#include <olibs/base/optr.hh>

#include <vector>


namespace Owui {
namespace Fcgi {

  
// упаковываем сюда то что требует включения fcgi h файлов
// они всякую бурду тянут, которую стоит изолировать в C файле
struct FcgiInternal
{
  virtual ~FcgiInternal() {}
};
  
  
class FcgiGateway: public HttpGateway
{
public:

private:
  Optr<FcgiInternal>  m_fcgiInternal;
  String              m_socketPort;
  int                 m_listenQueueBacklog;
  
public:  
  FcgiGateway(ServletServer& servletServer, const String& socketPort, int listenQueueBacklog);
  
  void run();
  
private:
  HttpRequest* createHttpRequest();
  void readContent(Buf<Byte>& buf);
  Int4 getContentLen(const HttpRequest::Env& env) const;
  
  
protected:
  virtual RequestContext* acceptRequest();
};


} // namespace Fcgi
} // namespace Owui

#endif // _OWUI_FCGI_GATEWAY_HH_

