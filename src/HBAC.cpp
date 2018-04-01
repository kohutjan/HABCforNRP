#include "HBAC.hpp"

using namespace std;

void HBAC::InitRosters()
{
  Roster roster;
  roster.Init(schedulingPeriod.startDate, schedulingPeriod.endDate,
              schedulingPeriod.employees, schedulingPeriod.shifts,
              schedulingPeriod.dayOfWeekCover,
              schedulingPeriod.dateSpecificCover);
  roster.Print();
}
