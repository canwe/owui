#ifndef __INDEXPAGEDATARTOHH_
#define __INDEXPAGEDATARTOHH_
#include <olibs/rto/dynamic.hh>

namespace Olibs{ namespace Rto { class HiMeta; } }

#include <olibs/rto/typesInfo.hh>
#include <olibs/base/types.hh>

class IndexPageData; 


class IndexPageData : public Olibs::Rto::Dynamic
{
public:
  IndexPageData();
  IndexPageData(const Olibs::Rto::HiMeta& meta);
  enum {fid_greeting, fid_lastVisit, fid_now, fid_clockColor, fid_name, fid_secondName};

  Olibs::String getGreeting() const ;
  void setGreeting(Olibs::String const& );

  Olibs::String getLastVisit() const ;
  void setLastVisit(Olibs::String const& );

  Olibs::Rto::DateTimeDynamic getNow() const ;
  void setNow(Olibs::Rto::DateTimeDynamic const& );

  Olibs::String getClockColor() const ;
  void setClockColor(Olibs::String const& );

  Olibs::String getName() const ;
  void setName(Olibs::String const& );

  Olibs::String getSecondName() const ;
  void setSecondName(Olibs::String const& );

  static const Olibs::Rto::HiMeta& staticMeta();

private:
  static Olibs::Rto::HiMeta* createMeta();
};

#endif
