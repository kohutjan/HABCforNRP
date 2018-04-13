#ifndef PENALTY_HPP
#define PENALTY_HPP


class Penalty
{
  public:
    Penalty(){}
    int NumAssigments;
    int ConsecutiveWorkingDays;
    int ConsecutiveFreeDays;
    int ConsecutiveWorkingWeekends;
    int MaxWorkingWeekendsInFourWeeks;
    int CompleteWeekends;
    int IdentShiftTypesDuringWeekend;
    int NoNightShiftBeforeFreeWeekend;
    int TwoFreeDaysAfterNightShifts;
    int RequestedDays;
    int RequstedShifts;
    int AlternativeSkillCategory;
    int UnwantedPatterns;
    ~Penalty(){}
};

#endif
