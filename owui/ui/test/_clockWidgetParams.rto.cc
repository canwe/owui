#include "_clockWidgetParams.rto.hh"
#include <olibs/rto/metaCache.hh>
#include <olibs/rto/meta.hh>



ClockWidgetParams::ClockWidgetParams() : Olibs::Rto::Dynamic(staticMeta()) {}
ClockWidgetParams::ClockWidgetParams(const Olibs::Rto::HiMeta& meta) : Olibs::Rto::Dynamic(meta) {}
Olibs::Rto::HiMeta* ClockWidgetParams::createMeta()
{
  Olibs::Rto::HiMeta* meta = new Olibs::Rto::HiMeta();
  meta->addField(fid_format, "format", new Olibs::Rto::Tmeta<Olibs::String>());
  meta->addField(fid_color, "color", new Olibs::Rto::Tmeta<Olibs::String>());
  return meta;
}
void ClockWidgetParams::setFormat(Olibs::String const& format)
{
  Olibs::Rto::Dynamic::at<Olibs::String>(fid_format) = format;
}

Olibs::String ClockWidgetParams::getFormat() const
{
  return Olibs::Rto::Dynamic::at<Olibs::String>(fid_format);
}

void ClockWidgetParams::setColor(Olibs::String const& color)
{
  Olibs::Rto::Dynamic::at<Olibs::String>(fid_color) = color;
}

Olibs::String ClockWidgetParams::getColor() const
{
  return Olibs::Rto::Dynamic::at<Olibs::String>(fid_color);
}

const Olibs::Rto::HiMeta& ClockWidgetParams::staticMeta()
{
  using namespace Olibs::Rto;
  Meta* meta = MetaCache::instance()->find("ClockWidgetParams");
  if(meta == 0)
  {
    meta = createMeta();
    MetaCache::instance()->put(meta, "ClockWidgetParams");
  }
  return *((HiMeta*)meta);
}

