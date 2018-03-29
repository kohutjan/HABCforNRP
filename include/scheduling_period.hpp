#ifndef SCHEDULING_PERIOD_HPP
#define SCHEDULING_PERIOD_HPP

#include <string>
#include <fstream>
#include <map>
#include <utility>
#include "boost/date_time/gregorian/gregorian.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"

class SchedulingPeriod
{
  public:
    SchedulingPeriod(){};
    bool Load(std::string periodFilePath);
    void LoadFromStream(std::ifstream &filtersStream);
    ~SchedulingPeriod(){}
  private:
    void LoadPeriod(std::ifstream &filtersStream);
    void LoadShiftTypes(std::ifstream &periodStream);
    std::string name;
    boost::gregorian::date startDate;
    boost::gregorian::date endDate;
    std::map<char, std::pair<boost::posix_time::time_duration, boost::posix_time::time_duration>> shiftTypes;
};

#endif
