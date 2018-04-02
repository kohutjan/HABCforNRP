#include "HBAC.hpp"

using namespace std;
using namespace boost::gregorian;

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
  cout << endl;
  cout << "daysOfWeek" << endl;
  for (auto& day: roster.daysOfWeek)
  {
    cout << day << " ";
  }
  cout << endl;
  cout << endl;
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
    penalty += this->CheckConsecutiveWorkingWeekends(roster.table.row(i), roster.daysOfWeek,
                                                     employeeContract.maxConsecutiveWorkingWeekends,
                                                     employeeContract.minConsecutiveWorkingWeekends);
    penalty += this->CheckMaxWorkingWeekendsInFourWeeks(roster.table.row(i), roster.daysOfWeek,
                                                        employeeContract.maxWorkingWeekendsInFourWeeks);
    penalty += this->CheckCompleteWeekends(roster.table.row(i), roster.daysOfWeek,
                                           employeeContract.completeWeekends);
    penalty += this->CheckIdentShiftTypesDuringWeekend(roster.table.row(i),
                                                       roster.daysOfWeek,
                                                       employeeContract.identShiftTypesDuringWeekend);
    penalty += this->CheckNoNightShiftBeforeFreeWeekend(roster.table.row(i),
                                                        roster.daysOfWeek,
                                                        employeeContract.noNightShiftBeforeFreeWeekend);
    penalty += this->CheckTwoFreeDaysAfterNightShifts(roster.table.row(i),
                                                      employeeContract.twoFreeDaysAfterNightShifts);
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
      penalty += maxNumAssignments.weight * (numAssignments - maxNumAssignments.value);
    }
  }
  if (minNumAssignments.on)
  {
    cout << "Min: " << minNumAssignments.value << endl;
    if (numAssignments < minNumAssignments.value)
    {
      penalty += minNumAssignments.weight * (minNumAssignments.value - numAssignments);
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

int HBAC::CheckConsecutiveWorkingWeekends(Row employeesShifts,
                                          vector<greg_weekday> daysOfWeek,
                                          Constrain maxConsecutiveWorkingWeekends,
                                          Constrain minConsecutiveWorkingWeekends)
{
  cout << "CheckConsecutiveWorkingWeekends" << endl;
  int penalty = 0;
  if ((!maxConsecutiveWorkingWeekends.on) && (!minConsecutiveWorkingWeekends.on))
  {
    cout << "none" << endl;
    return 0;
  }
  int actualConsecutive = 0;
  for (int i = 0; i < employeesShifts.size(); ++i)
  {
    if (daysOfWeek[i] == boost::date_time::Saturday)
    {
      if ((i + 1) < employeesShifts.size())
      {
        if (employeesShifts[i] != '-' && employeesShifts[i + 1] != '-')
        {
          ++actualConsecutive;
        }
        else
        {
          if (actualConsecutive != 0)
          {
            penalty += this->CheckConsecutive(actualConsecutive,
                                              maxConsecutiveWorkingWeekends,
                                              minConsecutiveWorkingWeekends);
            actualConsecutive = 0;
          }
        }
      }
    }
  }
  if (actualConsecutive > 0)
  {
    penalty += this->CheckConsecutive(actualConsecutive,
                                      maxConsecutiveWorkingWeekends,
                                      minConsecutiveWorkingWeekends);
  }
  if (maxConsecutiveWorkingWeekends.on)
  {
    cout << "Max: " << maxConsecutiveWorkingWeekends.value << endl;
  }
  if (minConsecutiveWorkingWeekends.on)
  {
    cout << "Min: " << minConsecutiveWorkingWeekends.value << endl;
  }
  cout << "penalty: " << penalty << endl;
  return penalty;
}

int HBAC::CheckMaxWorkingWeekendsInFourWeeks(Row employeesShifts,
                                             vector<greg_weekday> daysOfWeek,
                                             Constrain maxWorkingWeekendsInFourWeeks)
{
  cout << "CheckMaxWorkingWeekendsInFourWeeks" << endl;
  int penalty = 0;
  if (!maxWorkingWeekendsInFourWeeks.on)
  {
    cout << "none" << endl;
    return 0;
  }
  int numberOfWorkingWeeks = 0;
  for (int i = 0; i < employeesShifts.size(); ++i)
  {
    if (daysOfWeek[i] == boost::date_time::Saturday)
    {
      if ((i + 1) < employeesShifts.size())
      {
        if (employeesShifts[i] != '-' && employeesShifts[i + 1] != '-')
        {
          ++numberOfWorkingWeeks;
        }
        ++i;
      }
    }
  }
  cout << "Max: " << maxWorkingWeekendsInFourWeeks.value << endl;
  cout << "num: " << numberOfWorkingWeeks << endl;
  if (numberOfWorkingWeeks > maxWorkingWeekendsInFourWeeks.value)
  {
    penalty += numberOfWorkingWeeks - maxWorkingWeekendsInFourWeeks.value;
  }
  cout << "penalty: " << penalty << endl;
  return penalty;
}

int HBAC::CheckCompleteWeekends(Row employeesShifts, vector<greg_weekday> daysOfWeek,
                                Constrain completeWeekends)
{
  cout << "CheckCompleteWeekends" << endl;
  int penalty = 0;
  if (!completeWeekends.on)
  {
    cout << "none" << endl;
    return 0;
  }
  for (int i = 0; i < employeesShifts.size(); ++i)
  {
    if (daysOfWeek[i] == boost::date_time::Saturday)
    {
      if ((i + 1) < employeesShifts.size())
      {
        bool uncompleteWeekend = ((employeesShifts[i] == '-' &&
                                 employeesShifts[i + 1] != '-') ||
                                (employeesShifts[i] != '-' &&
                                 employeesShifts[i + 1] == '-'));
        if (uncompleteWeekend)
        {
          ++penalty;
        }
        ++i;
      }
    }
  }
  penalty *= completeWeekends.weight;
  cout << "penalty: " << penalty << endl;
  return penalty;
}

int HBAC::CheckIdentShiftTypesDuringWeekend(Row employeesShifts,
                                            vector<greg_weekday> daysOfWeek,
                                            Constrain identShiftTypesDuringWeekend)
{
  cout << "CheckIdentShiftTypesDuringWeekend" << endl;
  int penalty = 0;
  if (!identShiftTypesDuringWeekend.on)
  {
    cout << "none" << endl;
    return 0;
  }
  for (int i = 0; i < employeesShifts.size(); ++i)
  {
    if (daysOfWeek[i] == boost::date_time::Saturday)
    {
      if ((i + 1) < employeesShifts.size())
      {
        bool nonidentWeekend = ((employeesShifts[i] != employeesShifts[i + 1]) &&
                                (employeesShifts[i] != '-' && employeesShifts[i + 1] != '-'));
        if (nonidentWeekend)
        {
          ++penalty;
        }
        ++i;
      }
    }
  }
  penalty *= identShiftTypesDuringWeekend.weight;
  cout << "penalty: " << penalty << endl;
  return penalty;
}

int HBAC::CheckNoNightShiftBeforeFreeWeekend(Row employeesShifts,
                                             vector<greg_weekday> daysOfWeek,
                                             Constrain noNightShiftBeforeFreeWeekend)
{
  cout << "CheckNoNightShiftBeforeFreeWeekend" << endl;
  int penalty = 0;
  if (!noNightShiftBeforeFreeWeekend.on)
  {
    cout << "none" << endl;
    return 0;
  }
  for (int i = 1; i < employeesShifts.size(); ++i)
  {
    if (daysOfWeek[i] == boost::date_time::Saturday)
    {
      if ((i + 1) < employeesShifts.size())
      {
        if (employeesShifts[i - 1] == 'N')
        {
          bool freeWeekend = (employeesShifts[i] == '-' && employeesShifts[i + 1] == '-');
          if (freeWeekend)
          {
            ++penalty;
          }
        }
        ++i;
      }
    }
  }
  penalty *= noNightShiftBeforeFreeWeekend.weight;
  cout << "penalty: " << penalty << endl;
  return penalty;
}


int HBAC::CheckTwoFreeDaysAfterNightShifts(Row employeesShifts,
                                           Constrain twoFreeDaysAfterNightShifts)
{
  cout << "CheckTwoFreeDaysAfterNightShifts" << endl;
  int penalty = 0;
  if (!twoFreeDaysAfterNightShifts.on)
  {
    cout << "none" << endl;
    return 0;
  }
  for (int i = 0; i < employeesShifts.size(); ++i)
  {
    if (employeesShifts[i] == 'N')
    {
      if ((i + 1) < employeesShifts.size())
      {
        if (employeesShifts[i + 1] != '-')
        {
          ++penalty;
        }
      }
      if ((i + 2) < employeesShifts.size())
      {
        if (employeesShifts[i + 2] != '-')
        {
          ++penalty;
        }
      }
    }
  }
  penalty *= twoFreeDaysAfterNightShifts.weight;
  cout << "penalty: " << penalty << endl;
  return penalty;
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

int HBAC::CheckConsecutive(int actualConsecutive, Constrain maxConsecutive,
                           Constrain minConsecutive)
{
  int penalty = 0;
  if (maxConsecutive.on)
  {
    if (actualConsecutive > maxConsecutive.value)
    {
      penalty += maxConsecutive.weight * (actualConsecutive - maxConsecutive.value);
    }
  }
  if (minConsecutive.on)
  {
    if (actualConsecutive < minConsecutive.value)
    {
      penalty += minConsecutive.weight * (minConsecutive.value - actualConsecutive);
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
