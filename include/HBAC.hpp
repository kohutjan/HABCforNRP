#ifndef HBAC_HPP
#define HBAC_HPP

#include <iostream>
#include <vector>
#include <eigen3/Eigen/Dense>

#include "scheduling_period.hpp"
#include "roster.hpp"

typedef Eigen::DenseBase<Eigen::Matrix<char, -1, -1>>::RowXpr Row;

class HBAC
{
  public:
    HBAC(){}
    void setSchedulingPeriod(SchedulingPeriod _schedulingPeriod)
    {
      schedulingPeriod = _schedulingPeriod;
    }
    void InitRosters(int numberOfRosters);
    int CheckNumAssigments(Row employeesShifts, Constrain maxNumAssignments,
                           Constrain minNumAssignments);
    int CheckConsecutiveWorkingDays(Row employeesShifts,
                                    Constrain maxConsecutiveWorkingDays,
                                    Constrain minConsecutiveWorkingDays);
    int CheckConsecutiveFreeDays(Row employeesShifts,
                                 Constrain maxConsecutiveFreeDays,
                                 Constrain minConsecutiveFreeDays);
    int CheckConsecutiveWorkingWeekends(Row employeesShifts,
                                        std::vector<boost::gregorian::greg_weekday> daysOfWeek,
                                        Constrain maxConsecutiveWorkingWeekends,
                                        Constrain minConsecutiveWorkingWeekends);
    int CheckMaxWorkingWeekendsInFourWeeks(Row employeesShifts,
                                           std::vector<boost::gregorian::greg_weekday> daysOfWeek,
                                           Constrain maxWorkingWeekendsInFourWeeks);
    int CheckCompleteWeekends(Row employeesShifts,
                              std::vector<boost::gregorian::greg_weekday> daysOfWeek,
                              Constrain completeWeekends);
    int CheckIdentShiftTypesDuringWeekend(Row employeesShifts,
                                          std::vector<boost::gregorian::greg_weekday> daysOfWeek,
                                          Constrain identShiftTypesDuringWeekend);
    int CheckNoNightShiftBeforeFreeWeekend(Row employeesShifts,
                                           std::vector<boost::gregorian::greg_weekday> daysOfWeek,
                                           Constrain noNightShiftBeforeFreeWeekend);
    int CheckTwoFreeDaysAfterNightShifts(Row employeesShifts,
                                         Constrain twoFreeDaysAfterNightShifts);
    int CheckConsecutiveDays(bool working, Row employeesShifts,
                             Constrain maxConsecutiveDays, Constrain minConsecutiveDays);
    int CheckConsecutive(int actualConsecutive, Constrain maxConsecutiveDays,
                         Constrain minConsecutiveDays);

    void TestRosters();
    ~HBAC(){}
  private:
    int ObjectiveFunction(Roster roster);
    SchedulingPeriod schedulingPeriod;
    std::vector<Roster> rosters;
};

#endif
