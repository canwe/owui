#ifndef _OWUI_BASE_REQUEST_HH_
#define _OWUI_BASE_REQUEST_HH_

#include <owui/base/base.hh>
#include <olibs/base/optr.hh>
#include <olibs/base/buf.hh>

#include <vector>
#include <map>

namespace Owui {
using namespace Olibs;


class HttpRequest
{
public:
  typedef std::map<String,String> Env;
  typedef std::map<String,String> Params;
  typedef std::map<String, String> Cookies;

public:
  HttpRequest(Env* env, Buf<Byte>& content);
  
  const Env& env() const {return *m_env;}
  String env(const String& name, bool chex = true) const;
  bool isEnv(const String& name) const;
  bool testEnv(const String& name, const String& value) const;
  void printEnv(Ostream& os) const;  
    
  const Params& params() const {return m_params;}
  String param(const String& name, bool chex = true) const;
  bool isParam(const String& name) const;
  bool testParam(const String& name, const String& value) const;
  
  const Cookies& cookies() const {return m_cookies;}
  String cookie(const String& name, bool chex = true) const;
  bool isCookie(const String& name) const;
  bool testCookie(const String& name, const String& value) const;

  String uri() const {return env("REQUEST_URI");}
  
private:
  Optr<Env> m_env;
  Params    m_params;
  Cookies   m_cookies;
  Buf<Byte> m_content;

  void parseParams();
  static std::pair<String, String> parseOneParam(const String& paramValue);
  static void splitParams(const String& qurey, std::vector<String>& params);
  
  void parseCookies();
  void parseOneCookie(String oneCookieStr);
};


} // namespace Owui

#endif // _OWUI_BASE_REQUEST_HH_

