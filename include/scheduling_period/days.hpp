#ifndef DAYS_HPP
#define DAYS_HPP

#define MONDAY 'm'
#define TUESDAY 't'
#define WEDNESDAY 'w'
#define THURSDAY 'h'
#define FRIDAY 'f'
#define SATURDAY 's'
#define SUNDAY 'u'

#include <string>
#include "boost/date_time/gregorian/gregorian.hpp"

inline char StrToDay(std::string str)
{
  if (str == "Monday") return MONDAY;
  if (str == "Tuesday") return TUESDAY;
  if (str == "Wednesday") return WEDNESDAY;
  if (str == "Thursday") return THURSDAY;
  if (str == "Friday") return FRIDAY;
  if (str == "Saturday") return SATURDAY;
  if (str == "Sunday") return SUNDAY;
  return 'n';
}

inline char GregToDay(boost::gregorian::greg_weekday greg)
{
  if (greg == boost::date_time::Monday) return MONDAY;
  if (greg == boost::date_time::Tuesday) return TUESDAY;
  if (greg == boost::date_time::Wednesday) return WEDNESDAY;
  if (greg == boost::date_time::Thursday) return THURSDAY;
  if (greg == boost::date_time::Friday) return FRIDAY;
  if (greg == boost::date_time::Saturday) return SATURDAY;
  if (greg == boost::date_time::Sunday) return SUNDAY;
  return 'n';
}

#endif
