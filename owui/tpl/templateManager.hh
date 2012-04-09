#ifndef _OWUI_TPL_TEMPLATE_MANAGER_HH_
#define _OWUI_TPL_TEMPLATE_MANAGER_HH_

#include <owui/tpl/base.hh>
#include <olibs/base/exception.hh>
#include <olibs/base/onlyOne.hh>
#include <olibs/base/debug.hh>
#include <map> 
#include <vector> 


namespace Owui {
namespace Tpl {

class Template;
class TagCatalog;
class Code;
class StaticContext;  

class TemplateManager: public OnlyOne<TemplateManager>
{
public:
  class TemplateNotFound : public StrEx
  {
  public:
    TemplateNotFound(const String& logicPath): StrEx(String("Template not found: ") + logicPath) {}
  };
  class TagInfoPageDataNotFound : public StrEx
  {
  public:
    TagInfoPageDataNotFound(const String& logicPath): StrEx(String("TagInfo page data not found: ") + logicPath) {}
  };
  
  
  struct SrcDir
  {
    String m_fsPath;
    String m_logicPathPrefix;
  };
  
  typedef std::map<String, Template*> Templates;
  typedef std::vector<SrcDir> SourceDirs;
  
  TemplateManager();
  ~TemplateManager();

  void setCodeCtx(StaticContext* codeCtx) {m_codeCtx = codeCtx;}

  void rescan(const TagCatalog* tagCatalog);
  void addSourceDir(const String& path, const String& logicPathPrefix);
  
  const Template* findTemplate(const String& logicPath) const;

  const SourceDirs& sourceDirs() const {return m_sourceDirs;}
  const Templates& templates() const   {return m_templates;}

  const StaticContext* codeCtx() const {OLIBS_ASSERT(m_codeCtx != 0); return m_codeCtx;}
  StaticContext* codeCtx() {OLIBS_ASSERT(m_codeCtx != 0); return m_codeCtx;}

private:
  StaticContext*  m_codeCtx;
  Templates       m_templates;
  SourceDirs      m_sourceDirs;

  void destroyTemplates();
  void compileSources(const TagCatalog* tagCatalog);
  void compileFromOneDir(const SrcDir& dir, const TagCatalog* tagCatalog);
  void compileOneTemplate(const String& name, const String& logicPath, const String& logicPathPrefix, const TagCatalog* tagCatalog);
  
  void chex(const String& fullLogicPath, const TagCatalog* tagCatalog, const Code& code);
};
   
   
} // namespace Tpl
} // namespace Owui  

#endif // _OWUI_TPL_TEMPLATE_MANAGER_HH_

