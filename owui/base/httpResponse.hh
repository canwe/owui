#ifndef _OWUI_BASE_RESPONSE_HH_
#define _OWUI_BASE_RESPONSE_HH_

#include <owui/base/cookie.hh>
#include <olibs/base/optr.hh>
#include <olibs/base/buf.hh>
#include <olibs/time/dateTime.hh>
#include <olibs/base/null.hh>

#include <set>
#include <vector>


namespace Owui {

class HttpResponse
{
public:
  typedef std::set<Cookie, Cookie::Less> Cookies;
  typedef std::vector<String> ExtraHeaders;

private:
  Optr<std::streambuf>  m_httpStreamBuf;
  Optr<Ostream>         m_httpStream;
 
  OstringStream         m_memStream;
  Cookies               m_cookies;
  String                m_contentType;
  bool                  m_isMemMode;
  ExtraHeaders          m_extraHeaders;

  void putCookies();
  void putExtraHeaders();
  
public:
  HttpResponse(std::streambuf* streamBuf);
  
  void setCookie(const Cookie& cookie)                         {m_cookies.insert(cookie);}
  const Cookies& cookies() const                               {return m_cookies;}

  void setContentType(const String& contentType = "text/html") {m_contentType = contentType;}
  const String& contentType() const                            {return m_contentType;}

  const ExtraHeaders& extraHeaders() const                     {return m_extraHeaders;}
  void addExtraHeader(const String& headerStr)                 {m_extraHeaders.push_back(headerStr);}
  
  Ostream& os();  
  void flushHeaders();
};
  

} // namespace Owui

#endif // _OWUI_BASE_RESPONSE_HH_

