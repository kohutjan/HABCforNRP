#ifndef SHIFT_HPP
#define SHIFT_HPP

#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include "boost/date_time/posix_time/posix_time.hpp"


class Shift
{
  public:
    Shift(){};
    void LoadFromStream(std::ifstream &periodStream);
    void LoadDayOfWeekCover(std::ifstream &periodStream);
    void LoadDateSpecificCover(std::ifstream &periodStream);
    char id;
    boost::posix_time::time_duration startTime;
    boost::posix_time::time_duration endTime;
    std::vector<std::string> skills;
    ~Shift(){}
};

#endif
