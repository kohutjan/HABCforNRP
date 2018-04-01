#ifndef HBAC_HPP
#define HBAC_HPP

#include <iostream>
#include <vector>
#include <eigen3/Eigen/Dense>

#include "scheduling_period.hpp"
#include "roster.hpp"

class HBAC
{
  public:
    HBAC(){}
    void setSchedulingPeriod(SchedulingPeriod _schedulingPeriod)
    {
      schedulingPeriod = _schedulingPeriod;
    }
    void InitRosters(int numberOfRosters);
    void TestRosters();
    ~HBAC(){}
  private:
    int ObjectiveFunction(Roster roster);
    SchedulingPeriod schedulingPeriod;
    std::vector<Roster> rosters;
};

#endif
