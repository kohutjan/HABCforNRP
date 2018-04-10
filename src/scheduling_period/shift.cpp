#include "scheduling_period/shift.hpp"


using namespace std;
using namespace boost::posix_time;


void Shift::LoadFromStream(ifstream &periodStream)
{
  string ignore;
  char charIgnore;
  periodStream >> charIgnore;
  if (charIgnore == 'D')
  {
    periodStream >> charIgnore;
    if (charIgnore == 'H')
    {
      this->id = 'H';
      periodStream >> ignore;
    }
    else
    {
      this->id = 'D';
    }
  }
  else
  {
    this->id = charIgnore;
    periodStream >> ignore;
  }
  cout << this->id << ", ";
  periodStream >> ignore;
  while (ignore.back() != ',')
  {
    periodStream >> ignore;
  }
  string startTimeString;
  string endTimeString;
  periodStream >> startTimeString;
  periodStream >> endTimeString;
  startTimeString.pop_back();
  endTimeString.pop_back();
  this->startTime = duration_from_string(startTimeString);
  this->endTime = duration_from_string(endTimeString);
  cout << this->startTime << ", " << this->endTime;
  int numberOfSkills;
  periodStream >> numberOfSkills;
  periodStream >> ignore;
  string skill;
  for (int i = 0; i < (numberOfSkills - 1); ++i)
  {
    periodStream >> skill;
    this->skills.push_back(skill);
    cout << ", " << this->skills[i];
  }
  periodStream >> skill;
  skill.pop_back();
  this->skills.push_back(skill);
  cout << ", " << this->skills.back();
  cout << endl;
  return;
}
