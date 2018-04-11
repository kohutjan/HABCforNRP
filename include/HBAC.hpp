#ifndef HBAC_HPP
#define HBAC_HPP

#include <iostream>
#include <vector>
#include <eigen3/Eigen/Dense>

#include "scheduling_period.hpp"
#include "roster.hpp"
#include "objective_function.hpp"
#include "neighbourhood.hpp"


class HBAC
{
  public:
    HBAC(){}
    HBAC(int _SN, int _MCN, int _limit) : SN(_SN), MCN(_MCN), limit(_limit){}
    void setSchedulingPeriod(SchedulingPeriod _schedulingPeriod)
    {
      schedulingPeriod = _schedulingPeriod;
      objectiveFunction = ObjectiveFunction(schedulingPeriod);
    }
    void InitRosters();
    void TestRosters();
    ~HBAC(){}
  private:
    SchedulingPeriod schedulingPeriod;
    ObjectiveFunction objectiveFunction;
    int SN;
    int MCN;
    int limit;
    std::vector<Roster> rosters;
};

#endif
