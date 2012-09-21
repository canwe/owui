#include <owui/tpl/opParametrs.hh>
#include <owui/tpl/codeOp.hh>
#include <olibs/base/assert.hh>
#include <sstream>


namespace Owui {
namespace Tpl {


OpParametr::OpParametr(const OpParametr& rhs)
{
  copy(rhs);
}

OpParametr& OpParametr::operator= (const OpParametr& rhs)
{
  copy(rhs);
  return *this;
}

OpParametr::~OpParametr()
{
  clear();
}

void OpParametr::copy(const OpParametr& rhs)
{
  clear();
  
  for(size_t i = 0; i < rhs.m_splinters.size(); ++i)
  {
    TextEmittingOp* ptr = rhs.m_splinters.at(i);
    OLIBS_ASSERT(ptr != 0);
    m_splinters.push_back(ptr->clone());
  }  
}

void OpParametr::addPart(TextEmittingOp* part)
{
  OLIBS_ASSERT(part != 0);
  m_splinters.push_back(part);
}

String OpParametr::calculate(DynamicContext& dctx) const
{
  OstringStream result;
  
  for(PartsContainer::const_iterator pos = m_splinters.begin(); pos != m_splinters.end(); ++pos)
  {
    TextEmittingOp* ptr = *pos;
    OLIBS_ASSERT(ptr != 0);
    ptr->exec(result, dctx);
  }
  
  return result.str();
}

void OpParametr::clear()
{
  for(size_t i = 0; i < m_splinters.size(); ++i)
  {
    TextEmittingOp* ptr = m_splinters.at(i);
    OLIBS_ASSERT(ptr != 0);
    delete ptr;
  }
  
  m_splinters.clear();  
}

OpNameValueParamsPair::OpNameValueParamsPair(const OpParametr& paramName, const OpParametr& paramValue) :
  m_paramName(paramName),
  m_paramValue(paramValue)
{}

String OpNameValueParamsPair::name(DynamicContext& dctx) const
{
  return m_paramName.calculate(dctx);
}

String OpNameValueParamsPair::value(DynamicContext& dctx) const
{
  return m_paramValue.calculate(dctx);  
}

void OpParametrs::fill(Olibs::Rto::Dynamic& dynamic, DynamicContext& dctx) const
{
  for(ParamsContainer::const_iterator pos = m_params.begin(); pos != m_params.end(); ++pos)
    dynamic.parseField(pos->value(dctx), pos->name(dctx));
}

void OpParametrs::add(const OpNameValueParamsPair& nameValue)
{
  m_params.push_back(nameValue);
}


}}