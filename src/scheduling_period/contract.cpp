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
  this->singleAssignmentPerDay = this->LoadConstrain(periodStream);
  this->maxNumAssignments = this->LoadConstrain(periodStream);
  this->minNumAssignments = this->LoadConstrain(periodStream);
  this->maxConsecutiveWorkingDays = this->LoadConstrain(periodStream);
  this->minConsecutiveWorkingDays = this->LoadConstrain(periodStream);
  this->maxConsecutiveFreeDays = this->LoadConstrain(periodStream);
  this->minConsecutiveFreeDays = this->LoadConstrain(periodStream);
  this->maxConsecutiveWorkingWeekends = this->LoadConstrain(periodStream);
  this->minConsecutiveWorkingWeekends = this->LoadConstrain(periodStream);
  this->maxWorkingWeekendsInFourWeeks = this->LoadConstrain(periodStream);
  periodStream >> this->weekendDefinition;
  this->weekendDefinition.pop_back();
  cout << this->weekendDefinition << ", ";
  this->completeWeekends = this->LoadConstrain(periodStream);
  this->identShiftTypesDuringWeekend = this->LoadConstrain(periodStream);
  this->noNightShiftBeforeFreeWeekend = this->LoadConstrain(periodStream);
  this->twoFreeDaysAfterNightShifts = this->LoadConstrain(periodStream);
  this->alternativeSkillCategory = this->LoadConstrain(periodStream);
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

Constrain Contract::LoadConstrain(ifstream &periodStream)
{
  char ignoreChar;
  string ignore;
  int on;
  int weight;
  periodStream >> ignoreChar;
  periodStream >> on;
  periodStream >> ignoreChar;
  periodStream >> weight;
  periodStream >> ignoreChar;
  if (ignoreChar == ')')
  {
    Constrain constrain(on, weight);
    cout << "(" << constrain.on << "|" << constrain.weight << "), ";
    periodStream >> ignore;
    return constrain;
  }
  else
  {
    int value;
    periodStream >> value;
    Constrain constrain(on, weight, value);
    cout << "(" << constrain.on << "|" << constrain.weight << "|" << constrain.value << "), ";
    periodStream >> ignore;
    return constrain;
  }
}
