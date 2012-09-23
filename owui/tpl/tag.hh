#ifndef _OWUI_TPL_TAG_HH_
#define _OWUI_TPL_TAG_HH_

#include <olibs/base/object.hh>
#include <olibs/base/debug.hh>
#include <owui/tpl/base.hh>
#include <owui/tpl/code.hh>


namespace Olibs {
namespace Rto {
class HiMeta;
class Dynamic;
}}

namespace Owui {
namespace Tpl {

  
class Tag;
class DynamicContext;

struct TagContext
{
  const Olibs::Rto::Dynamic* m_params;
  const Code::Commands* m_childCommands;
  DynamicContext* m_dctx;
  
//    const Olibs::Rto::Dynamic* m_import;  // Внешние данные которые будут видны (обычно из parrent widget)
//    String              m_tplFname;
};


struct TagInfo
{
  String              m_name;
  const Rto::HiMeta*  m_paramsMeta;
  const Rto::HiMeta*  m_tplDataMeta;

  TagInfo(const String& name, const Rto::HiMeta* paramsMeta, const Rto::HiMeta* tplDataMeta):
    m_name(name), m_paramsMeta(paramsMeta), m_tplDataMeta(tplDataMeta) {}  
};


class TagCatalog
{
public:
  virtual ~TagCatalog() {};

  virtual const TagInfo& findInfo(const String& tagName) const = 0;
};


class TagAllocator
{
public:
  virtual ~TagAllocator() {}
  
  virtual Tag* allocTag(const String& tagName) = 0;
  virtual void freeTag(Tag* tag) = 0;
};


class TagLock
{
  TagAllocator* m_allocator;
  Tag*          m_tag;
  
public:
  TagLock(TagAllocator* allocator, const String& tagName);  
  ~TagLock();
  
  bool empty() const {return m_tag == 0;}
  
  Tag* operator-> () const {OLIBS_ASSERT(!empty()); return m_tag;}
};

  
class Tag : public Olibs::Object
{
public:
  virtual void draw(Ostream& os, const TagContext& context) = 0;
};   
   
   
} // namespace Tpl
} // namespace Owui  

#endif // _OWUI_TPL_TAG_HH_
