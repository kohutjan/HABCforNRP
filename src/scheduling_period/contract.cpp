#include "scheduling_period/contract.hpp"


using namespace std;


void Contract::LoadFromStream(ifstream &periodStream)
{
  string ignore;
  periodStream >> this->id;
  cout << this->id << ", ";
  periodStream >> ignore;
  periodStream >> this->description;
  this->description.pop_back();
  cout << this->description << ", ";
  this->singleAssignmentPerDay = this->ConvertConstrainToVec(periodStream);
  this->maxNumAssignments = this->ConvertConstrainToVec(periodStream);
  this->minNumAssignments = this->ConvertConstrainToVec(periodStream);
  this->maxConsecutiveWorkingDays = this->ConvertConstrainToVec(periodStream);
  this->minConsecutiveWorkingDays = this->ConvertConstrainToVec(periodStream);
  this->maxConsecutiveFreeDays = this->ConvertConstrainToVec(periodStream);
  this->minConsecutiveFreeDays = this->ConvertConstrainToVec(periodStream);
  this->maxConsecutiveWorkingWeekends = this->ConvertConstrainToVec(periodStream);
  this->minConsecutiveWorkingWeekends = this->ConvertConstrainToVec(periodStream);
  this->maxWorkingWeekendsInFourWeeks = this->ConvertConstrainToVec(periodStream);
  periodStream >> this->weekendDefinition;
  this->weekendDefinition.pop_back();
  cout << this->weekendDefinition << ", ";
  this->completeWeekends = this->ConvertConstrainToVec(periodStream);
  this->identShiftTypesDuringWeekend = this->ConvertConstrainToVec(periodStream);
  this->noNightShiftBeforeFreeWeekend = this->ConvertConstrainToVec(periodStream);
  this->twoFreeDaysAfterNightShifts = this->ConvertConstrainToVec(periodStream);
  this->alternativeSkillCategory = this->ConvertConstrainToVec(periodStream);
  int numberOfUnwantedPatterns;
  int patternId;
  periodStream >> numberOfUnwantedPatterns;
  cout << numberOfUnwantedPatterns << ", ";
  periodStream >> ignore;
  for (int i = 0; i < numberOfUnwantedPatterns; ++i)
  {
    periodStream >> patternId;
    this->unwantedPatterns.push_back(patternId);
    cout << this->unwantedPatterns.back() << " ";
  }
  periodStream >> ignore;
  cout << endl;
  return;
}

vector<int> Contract::ConvertConstrainToVec(ifstream &periodStream)
{
  char ignoreChar;
  string ignore;
  vector<int> constrain(2);
  periodStream >> ignoreChar;
  int constrainVal;
  for (int i = 0; i < 2; ++i)
  {
    periodStream >> constrainVal;
    constrain[i] = constrainVal;
    periodStream >> ignoreChar;
  }
  cout << "(" << constrain[0] << "|" << constrain[1];
  if (ignoreChar == '|')
  {
    periodStream >> constrainVal;
    constrain.push_back(constrainVal);
    cout << "|" << constrain[2];
  }
  periodStream >> ignore;
  cout << "), ";
  return constrain;
}
