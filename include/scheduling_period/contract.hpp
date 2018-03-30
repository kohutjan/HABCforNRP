#ifndef CONTRACT_HPP
#define CONTRACT_HPP

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "scheduling_period/constrain.hpp"


class Contract
{
  public:
    Contract(){};
    void LoadFromStream(std::ifstream &periodStream);
    int id;
    std::string description;
    Constrain singleAssignmentPerDay;
    Constrain maxNumAssignments;
    Constrain minNumAssignments;
    Constrain maxConsecutiveWorkingDays;
    Constrain minConsecutiveWorkingDays;
    Constrain maxConsecutiveFreeDays;
    Constrain minConsecutiveFreeDays;
    Constrain maxConsecutiveWorkingWeekends;
    Constrain minConsecutiveWorkingWeekends;
    Constrain maxWorkingWeekendsInFourWeeks;
    std::string weekendDefinition;
    Constrain completeWeekends;
    Constrain identShiftTypesDuringWeekend;
    Constrain noNightShiftBeforeFreeWeekend;
    Constrain twoFreeDaysAfterNightShifts;
    Constrain alternativeSkillCategory;
    std::vector<int> unwantedPatterns;
    ~Contract(){}
  private:
    Constrain LoadConstrain(std::ifstream &periodStream);

};

#endif
