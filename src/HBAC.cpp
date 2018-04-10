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
    Employee employee = this->schedulingPeriod.employees[roster.employeeIds[i]];
    int employeeContractId = employee.contractId;
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
                                                     employeeContract.weekendDefinition,
                                                     employeeContract.maxConsecutiveWorkingWeekends,
                                                     employeeContract.minConsecutiveWorkingWeekends);
    penalty += this->CheckMaxWorkingWeekendsInFourWeeks(roster.table.row(i), roster.daysOfWeek,
                                                        employeeContract.weekendDefinition,
                                                        employeeContract.maxWorkingWeekendsInFourWeeks);
    penalty += this->CheckCompleteWeekends(roster.table.row(i), roster.daysOfWeek,
                                           employeeContract.weekendDefinition,
                                           employeeContract.completeWeekends);
    penalty += this->CheckIdentShiftTypesDuringWeekend(roster.table.row(i),
                                                       roster.daysOfWeek,
                                                       employeeContract.weekendDefinition,
                                                       employeeContract.identShiftTypesDuringWeekend);
    penalty += this->CheckNoNightShiftBeforeFreeWeekend(roster.table.row(i),
                                                        roster.daysOfWeek,
                                                        employeeContract.weekendDefinition,
                                                        employeeContract.noNightShiftBeforeFreeWeekend);
    penalty += this->CheckTwoFreeDaysAfterNightShifts(roster.table.row(i),
                                                      employeeContract.twoFreeDaysAfterNightShifts);
    penalty += this->CheckRequestedDays(roster.table.row(i), roster.dates, employee);
    penalty += this->CheckRequstedShifts(roster.table.row(i), roster.dates, employee);
    penalty += this->CheckAlternativeSkillCategory(roster.table.row(i),
                                                   employeeContract.alternativeSkillCategory,
                                                   schedulingPeriod.shifts, employee);
    penalty += this->CheckUnwantedPatterns(roster.table.row(i), roster.daysOfWeek,
                                           employeeContract.unwantedPatterns,
                                           schedulingPeriod.patterns);
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
    if (employeesShifts[i] != NONE)
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
                                          vector<char> daysOfWeek,
                                          int weekendDefinition,
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
  if (weekendDefinition == SS)
  {
    for (int i = 0; i < employeesShifts.size(); ++i)
    {
      if (daysOfWeek[i] == SATURDAY)
      {
        if ((i + 1) < employeesShifts.size())
        {
          if (employeesShifts[i] != NONE && employeesShifts[i + 1] != NONE)
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
          ++i;
        }
      }
    }
  }
  if (weekendDefinition == FSS)
  {
    for (int i = 0; i < employeesShifts.size(); ++i)
    {
      if (daysOfWeek[i] == FRIDAY)
      {
        if ((i + 2) < employeesShifts.size())
        {
          if (employeesShifts[i] != NONE && employeesShifts[i + 1] != NONE
              && employeesShifts[i + 2] != NONE)
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
          i += 2;
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
                                             vector<char> daysOfWeek,
                                             int weekendDefinition,
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
  if (weekendDefinition == SS)
  {
    for (int i = 0; i < employeesShifts.size(); ++i)
    {
      if (daysOfWeek[i] == SATURDAY)
      {
        if ((i + 1) < employeesShifts.size())
        {
          if (employeesShifts[i] != NONE && employeesShifts[i + 1] != NONE)
          {
            ++numberOfWorkingWeeks;
          }
          ++i;
        }
      }
    }
  }
  if (weekendDefinition == FSS)
  {
    for (int i = 0; i < employeesShifts.size(); ++i)
    {
      if (daysOfWeek[i] == FRIDAY)
      {
        if ((i + 2) < employeesShifts.size())
        {
          if (employeesShifts[i] != NONE && employeesShifts[i + 1] != NONE
              && employeesShifts[i + 2] != NONE)
          {
            ++numberOfWorkingWeeks;
          }
          i += 2;
        }
      }
    }
  }
  cout << "Max: " << maxWorkingWeekendsInFourWeeks.value << endl;
  cout << "num: " << numberOfWorkingWeeks << endl;
  if (numberOfWorkingWeeks > maxWorkingWeekendsInFourWeeks.value)
  {
    penalty += maxWorkingWeekendsInFourWeeks.weight *
               (numberOfWorkingWeeks - maxWorkingWeekendsInFourWeeks.value);
  }
  cout << "penalty: " << penalty << endl;
  return penalty;
}

int HBAC::CheckCompleteWeekends(Row employeesShifts, vector<char> daysOfWeek,
                                int weekendDefinition, Constrain completeWeekends)
{
  cout << "CheckCompleteWeekends" << endl;
  int penalty = 0;
  if (!completeWeekends.on)
  {
    cout << "none" << endl;
    return 0;
  }
  if (weekendDefinition == SS)
  {
    for (int i = 0; i < employeesShifts.size(); ++i)
    {
      if (daysOfWeek[i] == SATURDAY)
      {
        if ((i + 1) < employeesShifts.size())
        {
          bool uncompleteWeekend = ((employeesShifts[i] == NONE &&
                                     employeesShifts[i + 1] != NONE) ||
                                    (employeesShifts[i] != NONE &&
                                     employeesShifts[i + 1] == NONE));
          if (uncompleteWeekend)
          {
            ++penalty;
          }
          ++i;
        }
      }
    }
  }
  if (weekendDefinition == FSS)
  {
    for (int i = 0; i < employeesShifts.size(); ++i)
    {
      if (daysOfWeek[i] == FRIDAY)
      {
        if ((i + 2) < employeesShifts.size())
        {
          int freeDays = 0;
          for (int j = 0; j < 3; ++j)
          {
            if (employeesShifts[i + j] == NONE)
            {
              ++freeDays;
            }
          }
          penalty += freeDays % 3;
          i += 2;
        }
      }
    }
  }
  penalty *= completeWeekends.weight;
  cout << "penalty: " << penalty << endl;
  return penalty;
}

int HBAC::CheckIdentShiftTypesDuringWeekend(Row employeesShifts,
                                            vector<char> daysOfWeek,
                                            int weekendDefinition,
                                            Constrain identShiftTypesDuringWeekend)
{
  cout << "CheckIdentShiftTypesDuringWeekend" << endl;
  int penalty = 0;
  if (!identShiftTypesDuringWeekend.on)
  {
    cout << "none" << endl;
    return 0;
  }
  if (weekendDefinition == SS)
  {
    for (int i = 0; i < employeesShifts.size(); ++i)
    {
      if (daysOfWeek[i] == SATURDAY)
      {
        if ((i + 1) < employeesShifts.size())
        {
          bool nonidentWeekend = ((employeesShifts[i] != employeesShifts[i + 1]) &&
                                  (employeesShifts[i] != NONE && employeesShifts[i + 1] != NONE));
          if (nonidentWeekend)
          {
            penalty += 2;
          }
          ++i;
        }
      }
    }
  }
  if (weekendDefinition == FSS)
  {
    for (int i = 0; i < employeesShifts.size(); ++i)
    {
      if (daysOfWeek[i] == FRIDAY)
      {
        if ((i + 2) < employeesShifts.size())
        {
          if (employeesShifts[i] != NONE && employeesShifts[i + 1] != NONE && employeesShifts[i + 2] != NONE)
          {
            char fridayShiftType = employeesShifts[i];
            char saturdayShiftType = employeesShifts[i + 1];
            char sundayShiftType = employeesShifts[i + 2];
            if ((fridayShiftType != saturdayShiftType && fridayShiftType != sundayShiftType && saturdayShiftType != sundayShiftType) ||
                (fridayShiftType != saturdayShiftType && fridayShiftType == sundayShiftType))
            {
              penalty += 2;
            }
            else
            {
              if ((fridayShiftType == saturdayShiftType && saturdayShiftType != sundayShiftType) ||
                  (fridayShiftType != saturdayShiftType && saturdayShiftType == sundayShiftType))
              {
                ++penalty;
              }
            }
          }
          i += 2;
        }
      }
    }
  }
  penalty *= identShiftTypesDuringWeekend.weight;
  cout << "penalty: " << penalty << endl;
  return penalty;
}

int HBAC::CheckNoNightShiftBeforeFreeWeekend(Row employeesShifts,
                                             vector<char> daysOfWeek,
                                             int weekendDefinition,
                                             Constrain noNightShiftBeforeFreeWeekend)
{
  cout << "CheckNoNightShiftBeforeFreeWeekend" << endl;
  int penalty = 0;
  if (!noNightShiftBeforeFreeWeekend.on)
  {
    cout << "none" << endl;
    return 0;
  }
  if (weekendDefinition == SS)
  {
    for (int i = 1; i < employeesShifts.size(); ++i)
    {
      if (daysOfWeek[i] == SATURDAY)
      {
        if ((i + 1) < employeesShifts.size())
        {
          if (employeesShifts[i - 1] == 'N')
          {
            bool freeWeekend = (employeesShifts[i] == NONE && employeesShifts[i + 1] == NONE);
            if (freeWeekend)
            {
              ++penalty;
            }
          }
          ++i;
        }
      }
    }
  }
  if (weekendDefinition == FSS)
  {
    for (int i = 1; i < employeesShifts.size(); ++i)
    {
      if (daysOfWeek[i] == FRIDAY)
      {
        if ((i + 2) < employeesShifts.size())
        {
          if (employeesShifts[i - 1] == 'N')
          {
            bool freeWeekend = (employeesShifts[i] == NONE &&
                                employeesShifts[i + 1] == NONE &&
                                employeesShifts[i + 2] == NONE);
            if (freeWeekend)
            {
              ++penalty;
            }
          }
          i += 2;
        }
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
        if (employeesShifts[i + 1] != NONE)
        {
          ++penalty;
        }
      }
      if ((i + 2) < employeesShifts.size())
      {
        if (employeesShifts[i + 2] != NONE)
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


int HBAC::CheckRequestedDays(Row employeesShifts, vector<date> dates, Employee employee)
{
  cout << "CheckRequestedDays" << endl;
  int penalty = 0;
  if (employee.dayOffRequest.empty() && employee.dayOnRequest.empty())
  {
    cout << "none" << endl;
    return 0;
  }
  if (!employee.dayOffRequest.empty())
  {
    for (int i = 0; i < employeesShifts.size(); ++i)
    {
      for (auto& dayOffRequest: employee.dayOffRequest)
      {
        if (dayOffRequest.first == dates[i])
        {
          if (employeesShifts[i] != NONE)
          {
            penalty += dayOffRequest.second;
          }
        }
      }
    }
  }
  if (!employee.dayOnRequest.empty())
  {
    for (int i = 0; i < employeesShifts.size(); ++i)
    {
      for (auto& dayOnRequest: employee.dayOnRequest)
      {
        if (dayOnRequest.first == dates[i])
        {
          if (employeesShifts[i] == NONE)
          {
            penalty += dayOnRequest.second;
          }
        }
      }
    }
  }
  cout << "penalty: " << penalty << endl;
  return penalty;
}


int HBAC::CheckRequstedShifts(Row employeesShifts, vector<date> dates, Employee employee)
{
  cout << "CheckRequestedShifts" << endl;
  int penalty = 0;
  if (employee.shiftOffRequest.empty() && employee.shiftOnRequest.empty())
  {
    cout << "none" << endl;
    return 0;
  }
  if (!employee.shiftOffRequest.empty())
  {
    for (int i = 0; i < employeesShifts.size(); ++i)
    {
      if (employee.shiftOffRequest.count(employeesShifts[i]) > 0)
      {
        for (auto& shiftOffRequest: employee.shiftOffRequest[employeesShifts[i]])
        {
          if (shiftOffRequest.first == dates[i])
          {
            penalty += shiftOffRequest.second;
          }
        }
      }
    }
  }
  if (employee.shiftOnRequest.empty())
  {
    for (int i = 0; i < employeesShifts.size(); ++i)
    {
      for (auto& shiftOnRequest: employee.shiftOnRequest)
      {
        char shiftType = shiftOnRequest.first;
        for (auto& onRequest: shiftOnRequest.second)
        {
          if (onRequest.first == dates[i])
          {
            if (employeesShifts[i] != shiftType)
            {
              penalty += onRequest.second;
            }
          }
        }
      }
    }
  }
  cout << "penalty: " << penalty << endl;
  return penalty;
}


int HBAC::CheckAlternativeSkillCategory(Row employeesShifts,
                                        Constrain alternativeSkillCategory,
                                        map<char, Shift> shifts,
                                        Employee employee)
{
  cout << "CheckAlternativeSkillCategory" << endl;
  int penalty = 0;
  if (!alternativeSkillCategory.on)
  {
    cout << "none" << endl;
    return 0;
  }
  for (int i = 0; i < employeesShifts.size(); ++i)
  {
    if (shifts.count(employeesShifts[i]) > 0)
    {
      for (auto& requiredSkill: shifts[employeesShifts[i]].skills)
      {
        bool skillFound = false;
        for (auto& employeeSkill: employee.skills)
        {
          if (requiredSkill == employeeSkill)
          {
            skillFound = true;
          }
        }
        if (!skillFound)
        {
          ++penalty;
        }
      }
    }
  }
  penalty *= alternativeSkillCategory.weight;
  cout << "penalty: " << penalty << endl;
  return penalty;
}


int HBAC::CheckUnwantedPatterns(Row employeesShifts, vector<char> daysOfWeek,
                                vector<int> unwantedPatterns, map<int, Pattern> patterns)
{
  cout << "CheckUnwantedPatterns" << endl;
  int penalty = 0;

  for (auto& unwantedPatternId: unwantedPatterns)
  {
    Pattern unwantedPattern = patterns[unwantedPatternId];
    for (int i = 0; i < employeesShifts.size(); ++i)
    {
      bool patternNotFound = true;
      int patternSize = static_cast<int>(unwantedPattern.shifts.size());
      if ((i + patternSize - 1) < employeesShifts.size())
      {
        patternNotFound = false;
        for (int j = 0; j < patternSize; ++j)
        {
          if (unwantedPattern.shifts[j].second != ANY)
          {
            if (unwantedPattern.shifts[j].second != daysOfWeek[i + j])
            {
              patternNotFound = true;
              break;
            }
          }
          if (unwantedPattern.shifts[j].first != ANY)
          {
            if (unwantedPattern.shifts[j].first != employeesShifts[i + j])
            {
              patternNotFound = true;
              break;
            }
          }
          else
          {
            if (employeesShifts[i + j] == NONE)
            {
              patternNotFound = true;
              break;
            }
          }
        }
      }
      if (!patternNotFound)
      {
        penalty += unwantedPattern.weight;
      }
    }
  }

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
    if ((employeesShifts[i] != NONE && working) || (employeesShifts[i] == NONE && !working))
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
