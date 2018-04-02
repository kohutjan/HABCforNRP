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
  int penalty = 0;
  for (int i = 0; i < roster.table.rows(); ++i)
  {
    int employeeContractId = this->schedulingPeriod.employees[roster.employeeIds[i]].contractId;
    Contract employeeContract = this->schedulingPeriod.contracts[employeeContractId];
    cout << endl;
    cout << "employee id: " << roster.employeeIds[i] << endl;
    cout << "------------------------------------" << endl;
    penalty += this->CheckNumAssigments(roster.table.row(i), employeeContract.maxNumAssignments,
                                        employeeContract.minNumAssignments);
    penalty += this->CheckConsecutiveWorkingDays(roster.table.row(i),
                                                 employeeContract.maxConsecutiveWorkingDays,
                                                 employeeContract.minConsecutiveWorkingDays);
    penalty += this->CheckConsecutiveFreeDays(roster.table.row(i),
                                              employeeContract.maxConsecutiveFreeDays,
                                              employeeContract.minConsecutiveFreeDays);
    cout << "------------------------------------" << endl;
  }
  return penalty;
}

int HBAC::CheckNumAssigments(Row employeesShifts, Constrain maxNumAssignments,
                             Constrain minNumAssignments)
{
  cout << "CheckNumAssigments" << endl;
  int penalty = 0;
  if ((!maxNumAssignments.on) && (!minNumAssignments.on))
  {
    cout << "none" << endl;
    return 0;
  }
  int numAssignments = 0;
  for (int i = 0; i < employeesShifts.size(); ++i)
  {
    if (employeesShifts[i] != '-')
    {
      ++numAssignments;
    }
  }
  if (maxNumAssignments.on)
  {
    cout << "Max: " << maxNumAssignments.value << endl;
    if (numAssignments > maxNumAssignments.value)
    {
      penalty += maxNumAssignments.weight;
    }
  }
  if (minNumAssignments.on)
  {
    cout << "Min: " << minNumAssignments.value << endl;
    if (numAssignments < minNumAssignments.value)
    {
      penalty += minNumAssignments.weight;
    }
  }
  cout << "num: " << numAssignments << endl;
  cout << "penalty: " << penalty << endl;
  return penalty;
}

int HBAC::CheckConsecutiveWorkingDays(Row employeesShifts,
                                      Constrain maxConsecutiveWorkingDays,
                                      Constrain minConsecutiveWorkingDays)
{
  cout << "CheckConsecutiveWorkingDays" << endl;
  return this->CheckConsecutiveDays(true, employeesShifts,
                                    maxConsecutiveWorkingDays, minConsecutiveWorkingDays);
}

int HBAC::CheckConsecutiveFreeDays(Row employeesShifts,
                                   Constrain maxConsecutiveFreeDays,
                                   Constrain minConsecutiveFreeDays)
{
  cout << "CheckConsecutiveFreeDays" << endl;
  return this->CheckConsecutiveDays(false, employeesShifts,
                                    maxConsecutiveFreeDays, minConsecutiveFreeDays);
}

int HBAC::CheckConsecutiveDays(bool working, Row employeesShifts,
                               Constrain maxConsecutiveDays,
                               Constrain minConsecutiveDays)
{
  int penalty = 0;
  if ((!maxConsecutiveDays.on) && (!minConsecutiveDays.on))
  {
    cout << "none" << endl;
    return 0;
  }
  int actualConsecutive = 0;
  for (int i = 0; i < employeesShifts.size(); ++i)
  {
    if ((employeesShifts[i] != '-' && working) || (employeesShifts[i] == '-' && !working))
    {
      ++actualConsecutive;
    }
    else
    {
      if (actualConsecutive != 0)
      {
        penalty += this->CheckConsecutive(actualConsecutive, maxConsecutiveDays,
                                          minConsecutiveDays);
        actualConsecutive = 0;
      }
    }
  }
  if (actualConsecutive > 0)
  {
    penalty += this->CheckConsecutive(actualConsecutive, maxConsecutiveDays,
                                      minConsecutiveDays);
  }
  if (maxConsecutiveDays.on)
  {
    cout << "Max: " << maxConsecutiveDays.value << endl;
  }
  if (minConsecutiveDays.on)
  {
    cout << "Min: " << minConsecutiveDays.value << endl;
  }
  cout << "penalty: " << penalty << endl;
  return penalty;
}

int HBAC::CheckConsecutive(int actualConsecutive, Constrain maxConsecutiveDays,
                           Constrain minConsecutiveDays)
{
  int penalty = 0;
  if (maxConsecutiveDays.on)
  {
    if (actualConsecutive > maxConsecutiveDays.value)
    {
      penalty += maxConsecutiveDays.weight;
    }
  }
  if (minConsecutiveDays.on)
  {
    if (actualConsecutive < minConsecutiveDays.value)
    {
      penalty += minConsecutiveDays.weight;
    }
  }
  return penalty;
}

void HBAC::TestRosters()
{
  int index = 0;
  for (auto& roster: rosters)
  {
    int penalty = this->ObjectiveFunction(roster);
    cout << endl;
    cout << endl;
    cout << "Objective function output for roster " << index << ": " << penalty;
    cout << endl;
    cout << endl;
    ++index;
  }

}
