#ifndef CONTRACT_HPP
#define CONTRACT_HPP

#include <string>
#include <vector>
#include <fstream>
#include <iostream>


class Contract
{
  public:
    Contract(){};
    void LoadFromStream(std::ifstream &filtersStream);
    int getId() { return id; }
    ~Contract(){}
  private:
    std::vector<int> ConvertConstrainToVec(std::ifstream &periodStream);
    int id;
    std::string description;
    std::vector<int> singleAssignmentPerDay;
    std::vector<int> maxNumAssignments;
    std::vector<int> minNumAssignments;
    std::vector<int> maxConsecutiveWorkingDays;
    std::vector<int> minConsecutiveWorkingDays;
    std::vector<int> maxConsecutiveFreeDays;
    std::vector<int> minConsecutiveFreeDays;
    std::vector<int> maxConsecutiveWorkingWeekends;
    std::vector<int> minConsecutiveWorkingWeekends;
    std::vector<int> maxWorkingWeekendsInFourWeeks;
    std::string weekendDefinition;
    std::vector<int> completeWeekends;
    std::vector<int> identShiftTypesDuringWeekend;
    std::vector<int> noNightShiftBeforeFreeWeekend;
    std::vector<int> twoFreeDaysAfterNightShifts;
    std::vector<int> alternativeSkillCategory;
    std::vector<int> unwantedPatterns;
};

#endif
