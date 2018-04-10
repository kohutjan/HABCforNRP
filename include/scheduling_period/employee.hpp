#ifndef EMPLOYEE_HPP
#define EMPLOYEE_HPP

#include <string>
#include <vector>
#include <map>
#include <utility>
#include <fstream>
#include <iostream>
#include "boost/date_time/gregorian/gregorian.hpp"

#include "scheduling_period/shift.hpp"

class Employee
{
  public:
    Employee(){};
    void LoadFromStream(std::ifstream &periodStream);
    void LoadDayRequest(std::ifstream &periodStream, bool on);
    void LoadShiftRequest(std::ifstream &periodStream, bool on);
    int id;
    std::string name;
    int contractId;
    std::vector<std::string> skills;
    std::vector<std::pair<boost::gregorian::date, int>> dayOffRequest;
    std::vector<std::pair<boost::gregorian::date, int>> dayOnRequest;
    std::map<char, std::vector<std::pair<boost::gregorian::date, int>>> shiftOffRequest;
    std::map<char, std::vector<std::pair<boost::gregorian::date, int>>> shiftOnRequest;
    ~Employee(){}
};

#endif
