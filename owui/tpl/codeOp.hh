#ifndef _OWUI_TPL_CODE_OP_HH_
#define _OWUI_TPL_CODE_OP_HH_

#include <owui/tpl/base.hh>
#include <iostream>
#include <string>


namespace Owui {
namespace Tpl {


class DynamicContext;


class CodeOp
{
public:
  virtual ~CodeOp(){}
  
  virtual void exec(Ostream& os, DynamicContext& dctx) const = 0;  
  virtual void print(Ostream& os, const String& prefix = "") const = 0;
};


class TextEmittingOp : public CodeOp
{
public:
  virtual ~TextEmittingOp(){}
  virtual TextEmittingOp* clone() = 0;
};


class OpWithNodes : public CodeOp
{
public:
  virtual ~OpWithNodes(){};
  virtual void attachSubNode(CodeOp* op) = 0;
};


} // namespace Tpl
} // namespace Owui

#endif // _OWUI_TPL_CODE_OP_HH_

