#include <owui/tpl/templateManager.hh>
#include <owui/tpl/template.hh>
#include <owui/tpl/parser.hh>
#include <owui/tpl/staticContext.hh>
#include <owui/tpl/tag.hh>

#include <olibs/file/dirScaner.hh>
#include <olibs/file/ut.hh>
#include <olibs/base/debug.hh>
#include <olibs/base/numberFormater.hh>
#include <olibs/str/ut.hh>
#include <olibs/txt/text.hh>

#include <fstream>

namespace Owui {
namespace Tpl {

  
const String templateExt = "wut";


TemplateManager::TemplateManager()
{
}

TemplateManager::~TemplateManager()
{
  destroyTemplates();
}

void TemplateManager::destroyTemplates()
{
  for(Templates::iterator it = m_templates.begin(); it != m_templates.end(); ++it)
    delete it->second;
}

void TemplateManager::rescan(const TagCatalog* tagCatalog)
{
  OLIBS_ASSERT(m_codeCtx != 0);
  OLIBS_ASSERT(tagCatalog != 0);
  
  destroyTemplates();
  compileSources(tagCatalog);
}

void TemplateManager::addSourceDir(const String& fsPath, const String& logicPathPrefix)
{
  SrcDir srcDir;
  srcDir.m_fsPath           = fsPath;
  srcDir.m_logicPathPrefix  = Str::toLower(logicPathPrefix);
  
  m_sourceDirs.push_back(srcDir);
}

void TemplateManager::compileSources(const TagCatalog* tagCatalog)
{
  for(SourceDirs::const_iterator it = m_sourceDirs.begin(); it != m_sourceDirs.end(); ++it)
    compileFromOneDir(*it, tagCatalog);
  
  OLIBS_DEBOUT("Amount of compiled templates: " + NumberFormater<long>() (m_templates.size()));
}

void TemplateManager::compileFromOneDir(const SrcDir& dir, const TagCatalog* tagCatalog)
{    
  File::DirScaner dirScaner(dir.m_fsPath);

  OLIBS_DEBOUT("I am scaning fs for templates (" + dir.m_fsPath + ")...");  
  const File::DirScaner::Entries& entries = dirScaner();  
  
  typedef File::DirScaner::Entries::const_iterator It;
  for(It it = entries.begin(); it != entries.end(); ++it)
  {
    if(File::extOfFname(it->m_name) == templateExt)
      compileOneTemplate(it->m_name, it->m_name.substr(dir.m_fsPath.length() + 1), dir.m_logicPathPrefix, tagCatalog);      
  }
}

const Template* TemplateManager::findTemplate(const String& logicPath) const
{
  Templates::const_iterator it = m_templates.find(logicPath);
  
  if(it == m_templates.end())
    return 0;
  
//    throw TemplateNotFound(logicPath);
  
  return it->second;
}

void TemplateManager::compileOneTemplate(const String& name, const String& logicPath, const String& logicPathPrefix, const TagCatalog* tagCatalog)
{
  OLIBS_ASSERT(tagCatalog != 0);
  OLIBS_DEBOUT("compiling template: " + name);
 
  Optr<Code> code(new Code);
  
  Txt::Text source(name);
  Parser parser(source, *code/*, *m_codeCtx*/);
  parser.parse();

  String fullLogicPath = Str::toLower(logicPathPrefix + File::fnameWithoutExt(logicPath));
  
  chex(fullLogicPath, tagCatalog, *code.get());
  
  Optr<Template> tpl(new Template(name, fullLogicPath, code.take())); 
  m_templates.insert(Templates::value_type(fullLogicPath, tpl.take())); 
}

void TemplateManager::chex(const String& fullLogicPath, const TagCatalog* tagCatalog, const Code& code)
{
  OLIBS_ASSERT(tagCatalog != 0);
  OLIBS_ASSERT(fullLogicPath != "");
  
  try
  {
    const TagInfo& tagInfo = tagCatalog->findInfo(fullLogicPath);
    
    if(tagInfo.m_tplDataMeta == 0)
      throw TagInfoPageDataNotFound(fullLogicPath);
    
    code.chex(tagInfo);
  }
  catch(Olibs::Rto::HiMeta::FieldNotFoundEx&)
  {
    throw;
  }
  catch(StrEx& ex)
  {
    OLIBS_DEBOUT(String("ex: ") + ex.what());
  }  
}


} // namespace Tpl
} // namespace Owui  

