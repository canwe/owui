#include <owui/tpl/executor.hh>
#include <owui/tpl/codeOp.hh>
#include <owui/tpl/code.hh>
#include <owui/tpl/staticContext.hh>
#include <owui/tpl/dynamicContext.hh>
#include <olibs/base/debug.hh>
#include <olibs/base/numberFormater.hh>


namespace Owui {
namespace Tpl {


Executor::Executor(const Code& code) :
  m_code(code)
{}
  
void Executor::exec(DynamicContext& dynamicContext, Ostream& out)
{
  OLIBS_DEBOUT("code size: " + NumberFormater<long>() (m_code.commands().size()));
  
  const Code::Commands& cmds = m_code.commands();
  typedef Code::Commands::const_iterator Cit;

  for(Cit ci = cmds.begin(); ci != cmds.end(); ++ci)
    (*ci)->exec(out, dynamicContext);
}


} // namespace Owui
} // namespace Tpl

