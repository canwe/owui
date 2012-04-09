#include <owui/base/httpRequest.hh>
#include <olibs/base/exception.hh>
#include <olibs/str/tokenizer.hh>
#include <olibs/str/ut.hh>
#include <stdexcept>
#include <sstream>

namespace Owui {

HttpRequest::HttpRequest(Env* env, Buf<Byte>& content) : 
  m_env(env)
{
  m_content.takeFrom(content);
  parseParams();
  parseCookies();
}    

String HttpRequest::env(const String& name, bool chex) const
{
  Env::const_iterator it = m_env->find(name);
  
  if(it == m_env->end())
  {
    if(chex)
      throw StrEx("Cannot find http env:" + name);
    else
      return "";
  }
  
  return it->second;
}

bool HttpRequest::isEnv(const String& name) const
{
  Env::const_iterator it = m_env->find(name);
  return it != m_env->end();
}

bool HttpRequest::testEnv(const String& name, const String& value) const
{
  return isEnv(name) && env(name) == value;
}

void HttpRequest::printEnv(Ostream& os) const
{
  for(Env::const_iterator it = env().begin(); it != env().end(); ++it)
    os << it->first << "=" << it->second << "<br/>\n";  
}

void HttpRequest::parseParams()
{
  String query = "";
  
  if(env("REQUEST_METHOD") == "GET")
  {
    query = env("QUERY_STRING");
  }
  else if(env("REQUEST_METHOD") == "POST")
  {
    String httpAccept = env("HTTP_ACCEPT");
    if(httpAccept.find("text") == String::npos)
      throw StrEx("unsupported request context");
    
    StringStream strStream;
    for(int i = 0; i < m_content.size(); ++i)
      strStream << m_content[i];
    
    query = strStream.str();
  }
  
  OLIBS_DEBOUT(query);
  
  std::vector<String> params;
  splitParams(query, params);
  
  for(unsigned i = 0; i < params.size(); ++i)
    m_params.insert(parseOneParam(params.at(i)));    
}

String HttpRequest::param(const String& name, bool chex) const
{
  Params::const_iterator it = m_params.find(name);
  
  if(it == m_params.end())
  {
    if(chex)
      throw StrEx("Cannot find http param:" + name);
    else
      return "";
  }
  
  return it->second;
}

bool HttpRequest::isParam(const String& name) const
{
  Params::const_iterator it = m_params.find(name);
  return it != m_params.end();
}

void HttpRequest::splitParams(const String& qurey, std::vector<String>& params)
{
  Olibs::Str::Tokenizer tok(qurey, '&');
  for(Olibs::Str::Tokenizer::iterator it = tok.begin(); it != tok.end(); ++it)
    if(*it != "")
      params.push_back(*it);   
}
  
std::pair<String, String> HttpRequest::parseOneParam(const String& paramValue)
{
  size_t position = paramValue.find('=');
  
  if(position == String::npos)
    throw std::runtime_error("bad format of value param pair");
  
  return std::make_pair(paramValue.substr(0, position), paramValue.substr(position + 1));
}

bool HttpRequest::testParam(const String& name, const String& value) const
{
  return isParam(name) && param(name) == value;
}

String HttpRequest::cookie(const String& name, bool chex) const
{
  Cookies::const_iterator it = m_cookies.find(name);
  
  if(it == m_cookies.end())
  {
    if(chex)
      throw StrEx("Cannot find http cookie:" + name);
    else
      return "";
  }
  
  return it->second;
}

bool HttpRequest::isCookie(const String& name) const
{
  Cookies::const_iterator it = m_cookies.find(name);
  return it != m_cookies.end();
}

bool HttpRequest::testCookie(const String& name, const String& value) const
{
  return isCookie(name) && cookie(name) == value;
}

void HttpRequest::parseCookies()
{
  String cookiesStr = env("HTTP_COOKIE", false);
OLIBS_DEBOUT(cookiesStr);
  if(cookiesStr.empty())
    return;
  
  Olibs::Str::Tokenizer tok(cookiesStr, ';');
  
  for(Olibs::Str::Tokenizer::iterator it = tok.begin(); it != tok.end(); ++it)
  {
    if(*it == "")
      continue;
    
    parseOneCookie(Str::truncate(*it));
  }
}

void HttpRequest::parseOneCookie(String oneCookieStr)
{
OLIBS_DEBOUT(oneCookieStr);

  size_t eqIdx = oneCookieStr.find('=');
  if(eqIdx == String::npos || eqIdx == 0)
    return;
  
  String name = Str::truncate(oneCookieStr.substr(0, eqIdx));
 
  String value = "";
  if(eqIdx < oneCookieStr.length()-1)
    value = Str::truncate(oneCookieStr.substr(eqIdx + 1));
  
  m_cookies.insert(Cookies::value_type(name, value));
  OLIBS_DEBOUT("C: " + name + "=" + value);
}


} // namespace Owui

