#include <owui/tpl/template.hh>


namespace Owui {
namespace Tpl {

  
Template::Template(const String& sourceFname, const String& logicPath, Code* code)
{
  m_sourceFname = sourceFname;
  m_logicPath   = logicPath;
  m_code.give(code);
}


} // namespace Tpl
} // namespace Owui  

