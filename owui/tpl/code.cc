#include <owui/tpl/code.hh>
#include <owui/tpl/codeOp.hh>
#include <olibs/base/assert.hh>
#include <owui/tpl/varOp.hh>
#include <owui/tpl/tag.hh>

using Owui::Tpl::Code;


Code::~Code()
{
  typedef Commands::iterator It;
  
  for(It it = m_commands.begin(); it != m_commands.end(); ++it)
    delete *it;
}

//----------------------------------------------------------------------------
void Code::print(Ostream& os, const String& prefix) const
{
  typedef Commands::const_iterator It;
  
  for(It it = m_commands.begin(); it != m_commands.end(); it++)
    (*it)->print(os, prefix + "  ");
}

void Code::registrateVariable(VarOp* var)
{
  OLIBS_ASSERT(var != 0);
  m_variables.push_back(var);
}

/* since all the query are requests to a parent widget (not to the index page!)*/
/* static checking of they correctness is no longer supported */
void Code::chex(const TagInfo& tagInfo)const
{
  /*
  const Rto::HiMeta* pageData = tagInfo.m_tplDataMeta;
  OLIBS_ASSERT(pageData != 0);

  typedef Variables::const_iterator It;
  for(It it = m_variables.begin(); it != m_variables.end(); ++it)
  {
    Owui::Tpl::VarOp* var = *it;
    OLIBS_ASSERT(var != 0);

    pageData->checkQuery(var->query());
  }  
  */
}
