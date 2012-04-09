#ifndef _OWUI_TPL_EXECUTOR_HH_
#define _OWUI_TPL_EXECUTOR_HH_

#include <owui/tpl/base.hh>


namespace Owui {
namespace Tpl {

  
class Code;
class StaticContext;
class DynamicContext;
  

class Executor
{
  const Code&          m_code;
  const StaticContext& m_staticContext;

public:
  Executor(const Code& code, const StaticContext& sctx);
  
  void exec(DynamicContext& dctx, Ostream& out);
};


} // namespace Tpl
} // namespace Owui


#endif // _OWUI_TPL_EXECUTOR_HH_

