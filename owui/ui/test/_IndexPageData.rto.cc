#include "_IndexPageData.rto.hh"
#include <olibs/rto/metaCache.hh>
#include <olibs/rto/meta.hh>



FullName::FullName() : Olibs::Rto::Dynamic(staticMeta()) {}
FullName::FullName(const Olibs::Rto::HiMeta& meta) : Olibs::Rto::Dynamic(meta) {}
Olibs::Rto::HiMeta* FullName::createMeta()
{
  Olibs::Rto::HiMeta* meta = new Olibs::Rto::HiMeta();
  meta->addField(fid_firsName, "firsName", new Olibs::Rto::Tmeta<Olibs::String>());
  meta->addField(fid_secondName, "secondName", new Olibs::Rto::Tmeta<Olibs::String>());
  return meta;
}
void FullName::setFirsName(Olibs::String const& firsName)
{
  Olibs::Rto::Dynamic::at<Olibs::String>(fid_firsName) = firsName;
}

Olibs::String FullName::getFirsName() const
{
  return Olibs::Rto::Dynamic::at<Olibs::String>(fid_firsName);
}

void FullName::setSecondName(Olibs::String const& secondName)
{
  Olibs::Rto::Dynamic::at<Olibs::String>(fid_secondName) = secondName;
}

Olibs::String FullName::getSecondName() const
{
  return Olibs::Rto::Dynamic::at<Olibs::String>(fid_secondName);
}

const Olibs::Rto::HiMeta& FullName::staticMeta()
{
  using namespace Olibs::Rto;
  Meta* meta = MetaCache::instance()->find("FullName");
  if(meta == 0)
  {
    meta = createMeta();
    MetaCache::instance()->put(meta, "FullName");
  }
  return *((HiMeta*)meta);
}



IndexPageData::IndexPageData() : Olibs::Rto::Dynamic(staticMeta()) {}
IndexPageData::IndexPageData(const Olibs::Rto::HiMeta& meta) : Olibs::Rto::Dynamic(meta) {}
Olibs::Rto::HiMeta* IndexPageData::createMeta()
{
  Olibs::Rto::HiMeta* meta = new Olibs::Rto::HiMeta();
  meta->addField(fid_greeting, "greeting", new Olibs::Rto::Tmeta<Olibs::String>());
  meta->addField(fid_lastVisit, "lastVisit", new Olibs::Rto::Tmeta<Olibs::String>());
  meta->addField(fid_now, "now", new Olibs::Rto::DateTimeDynamic());
  meta->addField(fid_clockColor, "clockColor", new Olibs::Rto::Tmeta<Olibs::String>());
  meta->addField(fid_name, "name", new Olibs::Rto::Tmeta<Olibs::String>());
  meta->addField(fid_secondName, "secondName", new Olibs::Rto::Tmeta<Olibs::String>());
  meta->addField(fid_names, "names", new Olibs::Rto::DynamicListOfDynamic());
  return meta;
}
void IndexPageData::setGreeting(Olibs::String const& greeting)
{
  Olibs::Rto::Dynamic::at<Olibs::String>(fid_greeting) = greeting;
}

Olibs::String IndexPageData::getGreeting() const
{
  return Olibs::Rto::Dynamic::at<Olibs::String>(fid_greeting);
}

void IndexPageData::setLastVisit(Olibs::String const& lastVisit)
{
  Olibs::Rto::Dynamic::at<Olibs::String>(fid_lastVisit) = lastVisit;
}

Olibs::String IndexPageData::getLastVisit() const
{
  return Olibs::Rto::Dynamic::at<Olibs::String>(fid_lastVisit);
}

void IndexPageData::setNow(Olibs::Rto::DateTimeDynamic const& now)
{
  Olibs::Rto::Dynamic::at<Olibs::Rto::DateTimeDynamic>(fid_now) = now;
}

Olibs::Rto::DateTimeDynamic IndexPageData::getNow() const
{
  return Olibs::Rto::Dynamic::at<Olibs::Rto::DateTimeDynamic>(fid_now);
}

void IndexPageData::setClockColor(Olibs::String const& clockColor)
{
  Olibs::Rto::Dynamic::at<Olibs::String>(fid_clockColor) = clockColor;
}

Olibs::String IndexPageData::getClockColor() const
{
  return Olibs::Rto::Dynamic::at<Olibs::String>(fid_clockColor);
}

void IndexPageData::setName(Olibs::String const& name)
{
  Olibs::Rto::Dynamic::at<Olibs::String>(fid_name) = name;
}

Olibs::String IndexPageData::getName() const
{
  return Olibs::Rto::Dynamic::at<Olibs::String>(fid_name);
}

void IndexPageData::setSecondName(Olibs::String const& secondName)
{
  Olibs::Rto::Dynamic::at<Olibs::String>(fid_secondName) = secondName;
}

Olibs::String IndexPageData::getSecondName() const
{
  return Olibs::Rto::Dynamic::at<Olibs::String>(fid_secondName);
}

void IndexPageData::setNames(Olibs::Rto::ListOfTypedDynamic<FullName>* const& names)
{
  Olibs::Rto::Dynamic::at<Olibs::Rto::ListOfTypedDynamic<FullName>*>(fid_names) = names;
}

Olibs::Rto::ListOfTypedDynamic<FullName>* IndexPageData::getNames() const
{
  return Olibs::Rto::Dynamic::at<Olibs::Rto::ListOfTypedDynamic<FullName>*>(fid_names);
}

const Olibs::Rto::HiMeta& IndexPageData::staticMeta()
{
  using namespace Olibs::Rto;
  Meta* meta = MetaCache::instance()->find("IndexPageData");
  if(meta == 0)
  {
    meta = createMeta();
    MetaCache::instance()->put(meta, "IndexPageData");
  }
  return *((HiMeta*)meta);
}

