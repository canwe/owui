#include <owui/fcgi/fcgiGateway.hh>
#include <owui/base/requestContext.hh>
#include <olibs/base/numberParser.hh>
#include <olibs/base/optr.hh>
#include <olibs/base/debug.hh>

#include <stdlib.h>

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif


// this inlude must be last
#include "fcgio.h"

#undef cerr
#undef cin
#undef cout


namespace Owui {
namespace Fcgi {


struct MyInternal: FcgiInternal
{
  FCGX_Request m_request;  
}; 
  

FcgiGateway::FcgiGateway(ServletServer& servletServer, const String& socketPort, int listenQueueBacklog):
HttpGateway(servletServer)  
{
  m_socketPort          = socketPort;
  m_listenQueueBacklog  = listenQueueBacklog;
  
  m_fcgiInternal.give(new MyInternal());
}

void FcgiGateway::run()
{
  MyInternal& myInternal = dynamic_cast<MyInternal&>(*m_fcgiInternal);
  
  FCGX_Init();
  
  int listenSocket = FCGX_OpenSocket(m_socketPort.c_str(), m_listenQueueBacklog);
  
  FCGX_InitRequest(&myInternal.m_request, listenSocket, 0);

//  Thr::Mutex acceptMutex;

  HttpGateway::run();
}

RequestContext* FcgiGateway::acceptRequest()
{
  OLIBS_DEBOUT("accept\n");
  MyInternal& myInternal = dynamic_cast<MyInternal&>(*m_fcgiInternal);
  int rc;
  
  {
//      Lock::Slock lock(acceptMutex);
    rc = FCGX_Accept_r(&myInternal.m_request);
  }
  
  if(rc < 0)
    return 0;
  
  Optr<HttpRequest> httpRequest(createHttpRequest());
  
  Optr<fcgi_streambuf> fcgiOutStreamBuf (new fcgi_streambuf(myInternal.m_request.out));
  
  return new RequestContext(httpRequest.take(), new HttpResponse(fcgiOutStreamBuf.take()));
}
  
HttpRequest* FcgiGateway::createHttpRequest()
{
  MyInternal& myInternal = dynamic_cast<MyInternal&>(*m_fcgiInternal);
  typedef HttpRequest::Env Env;
  
  Optr<Env> env(new Env); 

  const char** oneEnvPtr = const_cast<const char**>(myInternal.m_request.envp);

  for(; *oneEnvPtr != 0; ++oneEnvPtr)
  {
    String s = *oneEnvPtr;
    
    size_t delimPos = s.find('=');
    if(delimPos == String::npos || delimPos == 0)
      continue;
    
    String key = s.substr(0, delimPos);
    String value = (delimPos == s.length()-1) ? "" : s.substr(delimPos+1);
                          
    env->insert(std::make_pair(key, value));
  }
  
  Buf<Byte> content(getContentLen(*env.get()));
  readContent(content);
  
  return new HttpRequest(env.take(), content);
}

Int4 FcgiGateway::getContentLen(const HttpRequest::Env& env) const
{
  Int4 contentLen = 0;
  
  HttpRequest::Env::const_iterator it = env.find("CONTENT_LENGTH");
  if(it == env.end())
    return 0;
  
  String contentLenStr = it->second;
  OLIBS_ASSERT(contentLenStr != "");
  contentLen = NumberParser<Int4>()(contentLenStr);
  return contentLen;
}

void FcgiGateway::readContent(Buf<Byte>& buf)
{

  MyInternal& myInternal = dynamic_cast<MyInternal&>(*m_fcgiInternal);
  FCGX_Stream* inStream = myInternal.m_request.in;
  
  for(Int4 i = 0; i < buf.size(); ++i)
  {
    char c = FCGX_GetChar(inStream);
    OLIBS_ASSERT(c != EOF);
    buf[i] = c;
  }
  
  OLIBS_ASSERT(FCGX_GetChar(inStream) == EOF);
}


} // namespace Fcgi
} // namespace Owui

