#ifndef ROSTER_HPP
#define ROSTER_HPP

#include <eigen3/Eigen/Dense>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include "boost/date_time/gregorian/gregorian.hpp"

#include "scheduling_period/days.hpp"
#include "scheduling_period/employee.hpp"
#include "scheduling_period/shift.hpp"

class Roster
{
  public:
    Roster(){}
    void Init(boost::gregorian::date startDate, boost::gregorian::date endDate,
              std::map<int, Employee> employees, std::map<char, Shift> shifts,
              std::map<char, std::map<char, int>> dayOfWeekCover,
              std::map<std::string, std::map<char, int>> dateSpecificCover);
    std::vector<int> employeeIds;
    std::vector<char> daysOfWeek;
    std::vector<boost::gregorian::date> dates;
    Eigen::Matrix<char, Eigen::Dynamic, Eigen::Dynamic> table;
    void Print();
    ~Roster(){}
  private:
    void InitSumOfDemands(std::map<char, Shift> shifts,
                          std::map<char, std::map<char, int>> dayOfWeekCover);
    void InitShiftOrdering();
    void AssignShift(char shiftType,
                     std::map<char, std::map<char, int>> dayOfWeekCover,
                     std::map<std::string, std::map<char, int>> dateSpecificCover);
    void AssignShiftToDate(int dateIndex, char shiftType, int cover);
    int GetDayCover(int dateIndex, char shiftType,
                    std::map<char, std::map<char, int>> dayOfWeekCover);
    int GetDateCover(boost::gregorian::date specificDate, char shiftType,
                     std::map<std::string, std::map<char, int>> dateSpecificCover);
    std::map<char, int> sumOfDemands;
    std::vector<char> shiftOrdering;
};

#endif
