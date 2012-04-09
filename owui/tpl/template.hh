#ifndef _OWUI_TPL_TEMPLATE_HH_
#define _OWUI_TPL_TEMPLATE_HH_

#include <owui/tpl/code.hh>
#include <olibs/base/optr.hh>


namespace Olibs {
namespace Rto {
}}

namespace Owui {
namespace Tpl {

  
class Template
{
public:
  Template(const String& sourceFname, const String& logicPath, Code* code);
  
  const String& sourceFname() const {return m_sourceFname;}
  const String& logicPath() const   {return m_logicPath;}
  const Code& code() const          {return *m_code;}
  
private:
  String      m_sourceFname;
  String      m_logicPath;
  Optr<Code>  m_code;
};
   
   
} // namespace Tpl
} // namespace Owui  

#endif // _OWUI_TPL_TEMPLATE_HH_

