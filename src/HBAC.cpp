#include "HBAC.hpp"

using namespace std;

void HBAC::InitRosters(int numberOfRosters)
{
  for (int i = 0; i < numberOfRosters; ++i)
  {
    Roster roster;
    roster.Init(schedulingPeriod.startDate, schedulingPeriod.endDate,
                schedulingPeriod.employees, schedulingPeriod.shifts,
                schedulingPeriod.dayOfWeekCover,
                schedulingPeriod.dateSpecificCover);
    roster.Print();
    this->rosters.push_back(roster);
  }
}

int HBAC::ObjectiveFunction(Roster roster)
{
  return 0;
}

void HBAC::TestRosters()
{
  int index = 0;
  for (auto& roster: rosters)
  {
    cout << "Objective function output for roster " << index << ": ";
    cout << this->ObjectiveFunction(roster) << endl;
    ++index;
  }
}
