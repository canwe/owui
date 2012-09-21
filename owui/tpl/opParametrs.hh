#ifndef _OWUI_TPL_OPPARAMETRS_HH_
#define _OWUI_TPL_OPPARAMETRS_HH_

#include <owui/tpl/base.hh>
#include <olibs/rto/dynamic.hh>
#include <olibs/base/base.hh>
#include <olibs/base/types.hh>
#include <vector>


namespace Owui {
namespace Tpl {

  
class TextEmittingOp;  
class StaticContext;
class DynamicContext;

/*parametrs consist of texts and requests to page controller data*/  
/*they are calculated before passing to widget at run-time*/
/*it owns them*/
class OpParametr
{
public:
  OpParametr(){}
  OpParametr(const OpParametr&);
  
  ~OpParametr();
  
  OpParametr& operator= (const OpParametr&);  
  
  void addPart(TextEmittingOp* part);
  String calculate(DynamicContext& dctx) const;
  
  void clear();
  void copy(const OpParametr&);

private:
  typedef std::vector<TextEmittingOp*> PartsContainer;
  PartsContainer m_splinters;
};
  
class OpNameValueParamsPair
{
public:
  OpNameValueParamsPair(const OpParametr& paramName, const OpParametr& paramValue);
  ~OpNameValueParamsPair(){}
  
  String name(DynamicContext& dctx) const;
  String value(DynamicContext& dctx) const;  

private:
  OpParametr m_paramName;
  OpParametr m_paramValue;
};

typedef std::vector<std::pair<Olibs::String, Olibs::String> > OpTextParametrs;

class OpParametrs
{
public:
  OpParametrs(){}
  ~OpParametrs(){}
  
  void fill(Olibs::Rto::Dynamic& dynamic, DynamicContext& dctx) const;
  
  void add(const OpNameValueParamsPair& nameValue);
  
private:
  typedef std::vector<OpNameValueParamsPair> ParamsContainer;
  ParamsContainer m_params;
};


}}


#endif



