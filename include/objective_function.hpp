#ifndef OBJECTIVE_FUNCTION_HPP
#define OBJECTIVE_FUNCTION_HPP

#include <string>
#include <vector>
#include <iostream>
#include <eigen3/Eigen/Dense>

#include "scheduling_period.hpp"
#include "roster.hpp"

typedef Eigen::DenseBase<Eigen::Matrix<char, -1, -1>>::RowXpr Row;


class ObjectiveFunction
{
  public:
    ObjectiveFunction(SchedulingPeriod _schedulingPeriod) :
                      schedulingPeriod(_schedulingPeriod){};
    int CountPenalty(Roster roster);
    void setPrint() { print = true; }
    ~ObjectiveFunction(){}
  private:
    int CheckNumAssigments(Row employeesShifts, Constrain maxNumAssignments,
                           Constrain minNumAssignments);
    int CheckConsecutiveWorkingDays(Row employeesShifts,
                                    Constrain maxConsecutiveWorkingDays,
                                    Constrain minConsecutiveWorkingDays);
    int CheckConsecutiveFreeDays(Row employeesShifts,
                                 Constrain maxConsecutiveFreeDays,
                                 Constrain minConsecutiveFreeDays);
    int CheckConsecutiveWorkingWeekends(Row employeesShifts,
                                        std::vector<int> SSWeekendIndexes,
                                        std::vector<int> FSSWeekendIndexes,
                                        int weekendDefinition,
                                        Constrain maxConsecutiveWorkingWeekends,
                                        Constrain minConsecutiveWorkingWeekends);
    int CheckMaxWorkingWeekendsInFourWeeks(Row employeesShifts,
                                           std::vector<int> SSWeekendIndexes,
                                           std::vector<int> FSSWeekendIndexes,
                                           int weekendDefinition,
                                           Constrain maxWorkingWeekendsInFourWeeks);
    int CheckCompleteWeekends(Row employeesShifts,
                              std::vector<int> SSWeekendIndexes,
                              std::vector<int> FSSWeekendIndexes,
                              int weekendDefinition,
                              Constrain completeWeekends);
    int CheckIdentShiftTypesDuringWeekend(Row employeesShifts,
                                          std::vector<int> SSWeekendIndexes,
                                          std::vector<int> FSSWeekendIndexes,
                                          int weekendDefinition,
                                          Constrain identShiftTypesDuringWeekend);
    int CheckNoNightShiftBeforeFreeWeekend(Row employeesShifts,
                                           std::vector<int> SSWeekendIndexes,
                                           std::vector<int> FSSWeekendIndexes,
                                           int weekendDefinition,
                                           Constrain noNightShiftBeforeFreeWeekend);
    int CheckTwoFreeDaysAfterNightShifts(Row employeesShifts,
                                         Constrain twoFreeDaysAfterNightShifts);
    int CheckRequestedDays(Row employeesShifts, std::vector<boost::gregorian::date> dates,
                           Employee employee);
    int CheckRequstedShifts(Row employeesShifts, std::vector<boost::gregorian::date> dates,
                            Employee employee);
    int CheckAlternativeSkillCategory(Row employeesShifts, Constrain alternativeSkillCategory,
                                      std::map<char, Shift> shifts, Employee employee);
    int CheckUnwantedPatterns(Row employeesShifts, std::vector<char> daysOfWeek,
                              std::vector<int> unwantedPatterns,
                              std::map<int, Pattern> patterns);
    int CheckConsecutiveDays(bool working, Row employeesShifts,
                             Constrain maxConsecutiveDays, Constrain minConsecutiveDays);
    int CheckConsecutive(int actualConsecutive, Constrain maxConsecutiveDays,
                         Constrain minConsecutiveDays);
    SchedulingPeriod schedulingPeriod;
    bool print = false;
};

#endif
