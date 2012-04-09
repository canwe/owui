#ifndef _OWUI_BASE_COOKIE_HH_
#define _OWUI_BASE_COOKIE_HH_

#include <owui/base/base.hh>
#include <olibs/time/dateTime.hh>
#include <olibs/base/null.hh>

namespace Owui {

  
struct Cookie
{
  String                    m_name;
  String                    m_value;
  Nullable<Time::DateTime>  m_expire;
  String                    m_domain;
  String                    m_path;
  bool                      m_secure;
  bool                      m_httpOnly;
  
  Cookie();
  Cookie(const String& name, const String& value);
  Cookie(const String& name, const String& value, const Time::DateTime& expire);

  struct Less
  {
    bool operator() (const Cookie& c1, const Cookie& c2) const
      {return c1.m_name < c2.m_name;}
  };
};


} // namespace Owui

#endif // _OWUI_BASE_COOKIE_HH_

