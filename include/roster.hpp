#ifndef ROSTER_HPP
#define ROSTER_HPP

#include <eigen3/Eigen/Dense>
#include <iostream>
#include "boost/date_time/gregorian/gregorian.hpp"

#include "scheduling_period/employee.hpp"
#include "scheduling_period/shift.hpp"

class Roster
{
  public:
    Roster(){}
    void Init(boost::gregorian::date startDate, boost::gregorian::date endDate,
              std::map<int, Employee> employees, std::map<char, Shift> shifts,
              std::map<std::string, std::pair<char, int>> dayOfWeekCover,
              std::map<std::string, std::pair<char, int>> dateSpecificCover);
    Eigen::Matrix<char, Eigen::Dynamic, Eigen::Dynamic> table;
    void Print();
    ~Roster(){}
};

#endif
