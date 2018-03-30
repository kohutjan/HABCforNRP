#ifndef SCHEDULING_PERIOD_HPP
#define SCHEDULING_PERIOD_HPP

#include <string>
#include <fstream>
#include <map>
#include <utility>
#include "boost/date_time/gregorian/gregorian.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"

#include "scheduling_period/shift.hpp"
#include "scheduling_period/contract.hpp"
#include "scheduling_period/pattern.hpp"
#include "scheduling_period/employee.hpp"


class SchedulingPeriod
{
  public:
    SchedulingPeriod(){};
    bool Load(std::string periodFilePath);
    void LoadFromStream(std::ifstream &periodStream);
    ~SchedulingPeriod(){}
  private:
    void LoadPeriod(std::ifstream &periodStream);
    void LoadShifts(std::ifstream &periodStream);
    void LoadContracts(std::ifstream &periodStream);
    void LoadPatterns(std::ifstream &periodStream);
    void LoadEmployees(std::ifstream &periodStream);
    void LoadRequests(std::ifstream &periodStream, bool on, bool day);
    void LoadCover(std::ifstream &periodStream, bool day);
    template <typename I, typename P>
    std::map<I, P> LoadParam(std::ifstream &periodStream);
    std::string name;
    boost::gregorian::date startDate;
    boost::gregorian::date endDate;
    std::map<char, Shift> shifts;
    std::map<int, Contract> contracts;
    std::map<int, Pattern> patterns;
    std::map<int, Employee> employees;
    std::map<std::string, std::pair<char, int>> dayOfWeekCover;
    std::map<std::string, std::pair<char, int>> dateSpecificCover;
};

template <typename I, typename P>
std::map<I, P> SchedulingPeriod::LoadParam(std::ifstream &periodStream)
{
  std::string ignore;
  int numberOfLines;
  std::map<I, P> params;
  periodStream >> ignore;
  periodStream >> numberOfLines;
  periodStream >> ignore;
  periodStream >> ignore;
  for (int i = 0; i < numberOfLines; ++i)
  {
    P param;
    param.LoadFromStream(periodStream);
    params[param.id] = param;
  }
  return params;
}

#endif
