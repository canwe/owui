#ifndef __CLOCKWIDGETPARAMSRTOHH_
#define __CLOCKWIDGETPARAMSRTOHH_
#include <olibs/rto/dynamic.hh>

namespace Olibs{ namespace Rto { class HiMeta; } }

#include <olibs/base/types.hh>

class ClockWidgetParams; 


class ClockWidgetParams : public Olibs::Rto::Dynamic
{
public:
  ClockWidgetParams();
  ClockWidgetParams(const Olibs::Rto::HiMeta& meta);
  enum {fid_format, fid_color};

  Olibs::String getFormat() const ;
  void setFormat(Olibs::String const& );

  Olibs::String getColor() const ;
  void setColor(Olibs::String const& );

  static const Olibs::Rto::HiMeta& staticMeta();

private:
  static Olibs::Rto::HiMeta* createMeta();
};

#endif
