#ifndef HBAC_HPP
#define HBAC_HPP

#include <iostream>
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
    void InitRosters();
    ~HBAC(){}
  private:
    SchedulingPeriod schedulingPeriod;
};

#endif
