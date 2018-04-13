#include "objective_function.hpp"

using namespace std;
using namespace boost::gregorian;

int ObjectiveFunction::Forward(Roster roster)
{
  int penalty = 0;
  int constrainPenalty;
  if (this->print)
  {
    cout << endl;
    cout << "daysOfWeek" << endl;
    for (auto& day: roster.daysOfWeek)
    {
      cout << day << " ";
    }
    cout << endl;
    cout << endl;
  }
  for (int i = 0; i < roster.table.rows(); ++i)
  {
    Employee employee = this->schedulingPeriod.employees[roster.employeeIds[i]];
    int employeeContractId = employee.contractId;
    Contract employeeContract = this->schedulingPeriod.contracts[employeeContractId];
    if (print)
    {
      cout << endl;
      cout << "employee id: " << roster.employeeIds[i] << endl;
      cout << "------------------------------------" << endl;
    }

    constrainPenalty = this->CheckNumAssigments(roster.table.row(i), employeeContract.maxNumAssignments,
                                                employeeContract.minNumAssignments);
    if (print) cout << "CheckNumAssigments: " << constrainPenalty << endl;
    penalty += constrainPenalty;

    constrainPenalty = this->CheckConsecutiveWorkingDays(roster.table.row(i),
                                                         employeeContract.maxConsecutiveWorkingDays,
                                                         employeeContract.minConsecutiveWorkingDays);
    if (print) cout << "CheckConsecutiveWorkingDays: " << constrainPenalty << endl;
    penalty += constrainPenalty;

    constrainPenalty = this->CheckConsecutiveFreeDays(roster.table.row(i),
                                                      employeeContract.maxConsecutiveFreeDays,
                                                      employeeContract.minConsecutiveFreeDays);
    if (print) cout << "CheckConsecutiveFreeDays: " << constrainPenalty << endl;
    penalty += constrainPenalty;

    constrainPenalty = this->CheckConsecutiveWorkingWeekends(roster.table.row(i),
                                                             roster.SSWeekendIndexes, roster.FSSWeekendIndexes,
                                                             employeeContract.weekendDefinition,
                                                             employeeContract.maxConsecutiveWorkingWeekends,
                                                             employeeContract.minConsecutiveWorkingWeekends);
    if (print) cout << "CheckConsecutiveWorkingWeekends: " << constrainPenalty << endl;
    penalty += constrainPenalty;

    constrainPenalty = this->CheckMaxWorkingWeekendsInFourWeeks(roster.table.row(i),
                                                                roster.SSWeekendIndexes, roster.FSSWeekendIndexes,
                                                                employeeContract.weekendDefinition,
                                                                employeeContract.maxWorkingWeekendsInFourWeeks);
    if (print) cout << "CheckMaxWorkingWeekendsInFourWeeks: " << constrainPenalty << endl;
    penalty += constrainPenalty;

    constrainPenalty = this->CheckCompleteWeekends(roster.table.row(i),
                                                   roster.SSWeekendIndexes, roster.FSSWeekendIndexes,
                                                   employeeContract.weekendDefinition,
                                                   employeeContract.completeWeekends);
    if (print) cout << "CheckCompleteWeekends: " << constrainPenalty << endl;
    penalty += constrainPenalty;

    constrainPenalty = this->CheckIdentShiftTypesDuringWeekend(roster.table.row(i),
                                                               roster.SSWeekendIndexes, roster.FSSWeekendIndexes,
                                                               employeeContract.weekendDefinition,
                                                               employeeContract.identShiftTypesDuringWeekend);
    if (print) cout << "CheckIdentShiftTypesDuringWeekend: " << constrainPenalty << endl;
    penalty += constrainPenalty;

    constrainPenalty = this->CheckNoNightShiftBeforeFreeWeekend(roster.table.row(i),
                                                                roster.SSWeekendIndexes, roster.FSSWeekendIndexes,
                                                                employeeContract.weekendDefinition,
                                                                employeeContract.noNightShiftBeforeFreeWeekend);
    if (print) cout << "CheckNoNightShiftBeforeFreeWeekend: " << constrainPenalty << endl;
    penalty += constrainPenalty;

    constrainPenalty = this->CheckTwoFreeDaysAfterNightShifts(roster.table.row(i),
                                                              employeeContract.twoFreeDaysAfterNightShifts);
    if (print) cout << "CheckTwoFreeDaysAfterNightShifts: " << constrainPenalty << endl;
    penalty += constrainPenalty;

    constrainPenalty = this->CheckRequestedDays(roster.table.row(i), roster.dates, employee);
    if (print) cout << "CheckRequestedDays: " << constrainPenalty << endl;
    penalty += constrainPenalty;

    constrainPenalty = this->CheckRequstedShifts(roster.table.row(i), roster.dates, employee);
    if (print) cout << "CheckRequestedShifts: " << constrainPenalty << endl;
    penalty += constrainPenalty;

    constrainPenalty = this->CheckAlternativeSkillCategory(roster.table.row(i),
                                                           employeeContract.alternativeSkillCategory,
                                                           schedulingPeriod.shifts, employee);
    if (print) cout << "CheckAlternativeSkillCategory: " << constrainPenalty << endl;
    penalty += constrainPenalty;

    constrainPenalty = this->CheckUnwantedPatterns(roster.table.row(i), roster.daysOfWeek,
                                           employeeContract.unwantedPatterns,
                                           schedulingPeriod.patterns);
    if (print) cout << "CheckUnwantedPatterns: " << constrainPenalty << endl;
    penalty += constrainPenalty;

    if (print) cout << "------------------------------------" << endl;
  }
  return penalty;
}


int ObjectiveFunction::CheckNumAssigments(Row employeesShifts, Constrain maxNumAssignments,
                                          Constrain minNumAssignments)
{
  int penalty = 0;
  if ((!maxNumAssignments.on) && (!minNumAssignments.on))
  {
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
    if (numAssignments > maxNumAssignments.value)
    {
      penalty += maxNumAssignments.weight * (numAssignments - maxNumAssignments.value);
    }
  }
  if (minNumAssignments.on)
  {
    if (numAssignments < minNumAssignments.value)
    {
      penalty += minNumAssignments.weight * (minNumAssignments.value - numAssignments);
    }
  }
  return penalty;
}


int ObjectiveFunction::CheckConsecutiveWorkingDays(Row employeesShifts,
                                                   Constrain maxConsecutiveWorkingDays,
                                                   Constrain minConsecutiveWorkingDays)
{
  return this->CheckConsecutiveDays(true, employeesShifts,
                                    maxConsecutiveWorkingDays, minConsecutiveWorkingDays);
}


int ObjectiveFunction::CheckConsecutiveFreeDays(Row employeesShifts,
                                                Constrain maxConsecutiveFreeDays,
                                                Constrain minConsecutiveFreeDays)
{
  return this->CheckConsecutiveDays(false, employeesShifts,
                                    maxConsecutiveFreeDays, minConsecutiveFreeDays);
}


int ObjectiveFunction::CheckConsecutiveWorkingWeekends(Row employeesShifts,
                                                       vector<int> SSWeekendIndexes,
                                                       vector<int> FSSWeekendIndexes,
                                                       int weekendDefinition,
                                                       Constrain maxConsecutiveWorkingWeekends,
                                                       Constrain minConsecutiveWorkingWeekends)
{
  int penalty = 0;
  if ((!maxConsecutiveWorkingWeekends.on) && (!minConsecutiveWorkingWeekends.on))
  {
    return 0;
  }
  int actualConsecutive = 0;
  if (weekendDefinition == SS)
  {
    for (size_t i = 0; i < SSWeekendIndexes.size(); ++i)
    {
      int weekendIndex = SSWeekendIndexes[i];
      if (employeesShifts[weekendIndex] != NONE && employeesShifts[weekendIndex + 1] != NONE)
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
  if (weekendDefinition == FSS)
  {
    for (size_t i = 0; i < FSSWeekendIndexes.size(); ++i)
    {
      int weekendIndex = FSSWeekendIndexes[i];
      if (employeesShifts[weekendIndex] != NONE && employeesShifts[weekendIndex + 1] != NONE
          && employeesShifts[weekendIndex + 2] != NONE)
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
  if (actualConsecutive > 0)
  {
    penalty += this->CheckConsecutive(actualConsecutive,
                                      maxConsecutiveWorkingWeekends,
                                      minConsecutiveWorkingWeekends);
  }
  return penalty;
}


int ObjectiveFunction::CheckMaxWorkingWeekendsInFourWeeks(Row employeesShifts,
                                                          vector<int> SSWeekendIndexes,
                                                          vector<int> FSSWeekendIndexes,
                                                          int weekendDefinition,
                                                          Constrain maxWorkingWeekendsInFourWeeks)
{
  int penalty = 0;
  if (!maxWorkingWeekendsInFourWeeks.on)
  {
    return 0;
  }
  int numberOfWorkingWeeks = 0;
  if (weekendDefinition == SS)
  {
    for (size_t i = 0; i < SSWeekendIndexes.size(); ++i)
    {
      int weekendIndex = SSWeekendIndexes[i];
      if (employeesShifts[weekendIndex] != NONE && employeesShifts[weekendIndex + 1] != NONE)
      {
        ++numberOfWorkingWeeks;
      }
    }
  }
  if (weekendDefinition == FSS)
  {
    for (size_t i = 0; i < FSSWeekendIndexes.size(); ++i)
    {
      int weekendIndex = FSSWeekendIndexes[i];
      if (employeesShifts[weekendIndex] != NONE && employeesShifts[weekendIndex + 1] != NONE
          && employeesShifts[weekendIndex + 2] != NONE)
      {
        ++numberOfWorkingWeeks;
      }
    }
  }
  if (numberOfWorkingWeeks > maxWorkingWeekendsInFourWeeks.value)
  {
    penalty += maxWorkingWeekendsInFourWeeks.weight *
                       (numberOfWorkingWeeks - maxWorkingWeekendsInFourWeeks.value);
  }
  return penalty;
}


int ObjectiveFunction::CheckCompleteWeekends(Row employeesShifts,
                                             vector<int> SSWeekendIndexes,
                                             vector<int> FSSWeekendIndexes,
                                             int weekendDefinition, Constrain completeWeekends)
{
  int penalty = 0;
  if (!completeWeekends.on)
  {
    return 0;
  }
  if (weekendDefinition == SS)
  {
    for (size_t i = 0; i < SSWeekendIndexes.size(); ++i)
    {
      int weekendIndex = SSWeekendIndexes[i];
      bool uncompleteWeekend = ((employeesShifts[weekendIndex] == NONE &&
                                 employeesShifts[weekendIndex + 1] != NONE) ||
                                (employeesShifts[weekendIndex] != NONE &&
                                 employeesShifts[weekendIndex + 1] == NONE));
      if (uncompleteWeekend)
      {
        ++penalty;
      }
    }
  }
  if (weekendDefinition == FSS)
  {
    for (size_t i = 0; i < FSSWeekendIndexes.size(); ++i)
    {
      int weekendIndex = FSSWeekendIndexes[i];
      int freeDays = 0;
      for (int j = 0; j < 3; ++j)
      {
        if (employeesShifts[weekendIndex + j] == NONE)
        {
          ++freeDays;
        }
      }
      penalty += freeDays % 3;
    }
  }
  penalty *= completeWeekends.weight;
  return penalty;
}


int ObjectiveFunction::CheckIdentShiftTypesDuringWeekend(Row employeesShifts,
                                                         vector<int> SSWeekendIndexes,
                                                         vector<int> FSSWeekendIndexes,
                                                         int weekendDefinition,
                                                         Constrain identShiftTypesDuringWeekend)
{
  int penalty = 0;
  if (!identShiftTypesDuringWeekend.on)
  {
    return 0;
  }
  if (weekendDefinition == SS)
  {
    for (size_t i = 0; i < SSWeekendIndexes.size(); ++i)
    {
      int weekendIndex = SSWeekendIndexes[i];
      bool nonidentWeekend = ((employeesShifts[weekendIndex] != employeesShifts[weekendIndex + 1]) &&
                              (employeesShifts[weekendIndex] != NONE || employeesShifts[weekendIndex + 1] != NONE));
      if (nonidentWeekend)
      {
        penalty += 2;
      }
    }
  }
  if (weekendDefinition == FSS)
  {
    for (size_t i = 0; i < FSSWeekendIndexes.size(); ++i)
    {
      int weekendIndex = FSSWeekendIndexes[i];
      if (employeesShifts[weekendIndex] != NONE ||
          employeesShifts[weekendIndex + 1] != NONE ||
          employeesShifts[weekendIndex + 2] != NONE)
      {
        char fridayShiftType = employeesShifts[weekendIndex];
        char saturdayShiftType = employeesShifts[weekendIndex + 1];
        char sundayShiftType = employeesShifts[weekendIndex + 2];
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
    }
  }
  penalty *= identShiftTypesDuringWeekend.weight;
  return penalty;
}


int ObjectiveFunction::CheckNoNightShiftBeforeFreeWeekend(Row employeesShifts,
                                                          vector<int> SSWeekendIndexes,
                                                          vector<int> FSSWeekendIndexes,
                                                          int weekendDefinition,
                                                          Constrain noNightShiftBeforeFreeWeekend)
{
  int penalty = 0;
  if (!noNightShiftBeforeFreeWeekend.on)
  {
    return 0;
  }
  if (weekendDefinition == SS)
  {
    for (size_t i = 0; i < SSWeekendIndexes.size(); ++i)
    {
      int weekendIndex = SSWeekendIndexes[i];
      if ((weekendIndex - 1) >= 0)
      {
        if (employeesShifts[weekendIndex - 1] == NIGHT)
        {
          bool freeWeekend = (employeesShifts[weekendIndex] == NONE &&
                              employeesShifts[weekendIndex + 1] == NONE);
          if (freeWeekend)
          {
            ++penalty;
          }
        }
      }
    }
  }
  if (weekendDefinition == FSS)
  {
    for (size_t i = 0; i < FSSWeekendIndexes.size(); ++i)
    {
      int weekendIndex = FSSWeekendIndexes[i];

      if ((weekendIndex - 1) >= 0)
      {
        if (employeesShifts[weekendIndex - 1] == NIGHT)
        {
          bool freeWeekend = (employeesShifts[weekendIndex] == NONE &&
                              employeesShifts[weekendIndex + 1] == NONE &&
                              employeesShifts[weekendIndex + 2] == NONE);
          if (freeWeekend)
          {
            ++penalty;
          }
        }
      }
    }
  }
  penalty *= noNightShiftBeforeFreeWeekend.weight;
  return penalty;
}


int ObjectiveFunction::CheckTwoFreeDaysAfterNightShifts(Row employeesShifts,
                                                        Constrain twoFreeDaysAfterNightShifts)
{
  int penalty = 0;
  if (!twoFreeDaysAfterNightShifts.on)
  {
    return 0;
  }
  for (int i = 0; i < employeesShifts.size(); ++i)
  {
    if (employeesShifts[i] == NIGHT)
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
  return penalty;
}


int ObjectiveFunction::CheckRequestedDays(Row employeesShifts, vector<date> dates,
                                          Employee employee)
{
  int penalty = 0;
  if (employee.dayOffRequest.empty() && employee.dayOnRequest.empty())
  {
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
  return penalty;
}


int ObjectiveFunction::CheckRequstedShifts(Row employeesShifts, vector<date> dates,
                                           Employee employee)
{
  int penalty = 0;
  if (employee.shiftOffRequest.empty() && employee.shiftOnRequest.empty())
  {
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
  return penalty;
}


int ObjectiveFunction::CheckAlternativeSkillCategory(Row employeesShifts,
                                                     Constrain alternativeSkillCategory,
                                                     map<char, Shift> shifts,
                                                     Employee employee)
{
  int penalty = 0;
  if (!alternativeSkillCategory.on)
  {
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
  return penalty;
}


int ObjectiveFunction::CheckUnwantedPatterns(Row employeesShifts, vector<char> daysOfWeek,
                                             vector<int> unwantedPatterns,
                                             map<int, Pattern> patterns)
{
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
  return penalty;
}


int ObjectiveFunction::CheckConsecutiveDays(bool working, Row employeesShifts,
                                            Constrain maxConsecutiveDays,
                                            Constrain minConsecutiveDays)
{
  int penalty = 0;
  if ((!maxConsecutiveDays.on) && (!minConsecutiveDays.on))
  {
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
  return penalty;
}


int ObjectiveFunction::CheckConsecutive(int actualConsecutive, Constrain maxConsecutive,
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
