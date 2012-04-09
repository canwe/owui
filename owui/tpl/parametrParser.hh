#ifndef _OWUI_TPL_PARAMETRPARSER_HH_
#define _OWUI_TPL_PARAMETRPARSER_HH_


#include <olibs/base/base.hh>
#include <olibs/base/types.hh>
#include <owui/tpl/opParametrs.hh>
#include <vector>


namespace Owui {
namespace Tpl {


class ParametrParser
{
public:
  ParametrParser(){}
  ~ParametrParser(){}
  
  OpParametr exec(const Olibs::String& parametr);
  
  
private:
  void reset(const Olibs::String& processedString);  
  bool findQuery(size_t& startPos, size_t& afterEndPos, size_t currentPosition);
  void emitTextCode(size_t startPos, size_t size);
  void emitQueryCode(size_t startPos, size_t size);
  
  
private:
  static const Olibs::String m_queryStart;
  static const Olibs::String m_queryEnd;  
  
  OpParametr m_result;
  Olibs::String m_processedString;
};
  
  
}}

#endif