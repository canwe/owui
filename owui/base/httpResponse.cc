#include <owui/base/httpResponse.hh>

namespace Owui {


HttpResponse::HttpResponse(std::streambuf* streamBuf)
{
  m_httpStreamBuf.give(streamBuf);
  m_httpStream.give(new Ostream(m_httpStreamBuf.get()));
  
  m_isMemMode = true;
  m_contentType = "text/html";
}

Ostream& HttpResponse::os() 
{
  if(m_isMemMode)
    return m_memStream;
  else
    return *m_httpStream;
}  

void HttpResponse::flushHeaders()
{
  if(!m_isMemMode)
    return;
  
  *m_httpStream << "Content-type: " << contentType() << "\n";  
  putCookies();
  putExtraHeaders();
  *m_httpStream << "\n";  

  *m_httpStream << m_memStream.str();
    
  m_memStream.clear();
  m_isMemMode = false;
}

void HttpResponse::putCookies()
{
  for(Cookies::const_iterator it = m_cookies.begin(); it != m_cookies.end(); ++it)
  {
    *m_httpStream << "Set-Cookie: " << it->m_name << "=" << it->m_value;
    
    if(it->m_expire != Null())
      *m_httpStream << "; Expires=" << formatAsRFC822(*it->m_expire);
    
    if(!it->m_domain.empty())
      *m_httpStream << "; Domain=" << it->m_domain; 

    if(!it->m_path.empty())
      *m_httpStream << "; Path=" << it->m_path; 

    if(it->m_secure)
      *m_httpStream << "; Secure";

    if(it->m_httpOnly)
      *m_httpStream << "; HttpOnly"; 
    
    *m_httpStream << "\n";
  }
}

void HttpResponse::putExtraHeaders()
{
  for(ExtraHeaders::const_iterator it = m_extraHeaders.begin(); it != m_extraHeaders.end(); ++it)
    *m_httpStream << *it << "\n";
}

} // namespace Owui

