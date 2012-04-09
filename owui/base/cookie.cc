#include <owui/base/cookie.hh>

namespace Owui {

  
Cookie::Cookie()
{
  m_expire    = Null();
  m_secure    = false;
  m_httpOnly  = false;
}

Cookie::Cookie(const String& name, const String& value)
{
  m_name      = name;
  m_value     = value;
  m_expire    = Null();
  m_secure    = false;
  m_httpOnly  = false;
}

Cookie::Cookie(const String& name, const String& value, const Time::DateTime& expire)
{
  m_name      = name;
  m_value     = value;
  m_expire    = expire;
  m_secure    = false;
  m_httpOnly  = false;
}


} // namespace Owui

