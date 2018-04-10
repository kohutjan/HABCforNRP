#include "scheduling_period/employee.hpp"


using namespace std;
using namespace boost::gregorian;


void Employee::LoadFromStream(ifstream &periodStream)
{
  string ignore;
  periodStream >> this->id;
  cout << this->id << ", ";
  periodStream >> ignore;
  periodStream >> this->name;
  this->name.pop_back();
  cout << this->name << ", ";
  periodStream >> this->contractId;
  cout << this->contractId;
  periodStream >> ignore;
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

void Employee::LoadDayRequest(ifstream &periodStream, bool on)
{
  string ignore;
  string requestDateStr;
  periodStream >> requestDateStr;
  requestDateStr.pop_back();
  int weight;
  periodStream >> weight;
  periodStream >> ignore;
  date requestDate = from_simple_string(requestDateStr);
  cout << requestDate << ", " << weight << endl;
  if (on)
  {
    this->dayOnRequest.push_back(make_pair(requestDate, weight));
  }
  else
  {
    this->dayOffRequest.push_back(make_pair(requestDate, weight));
  }
  return;
}

void Employee::LoadShiftRequest(ifstream &periodStream, bool on)
{
  string ignore;
  string requestDateStr;
  periodStream >> requestDateStr;
  requestDateStr.pop_back();
  char shiftType;
  periodStream >> shiftType;
  if (shiftType == DAY)
  {
    periodStream >> shiftType;
    if (shiftType != HEAD_DAY)
    {
      shiftType = DAY;
    }
    else
    {
      periodStream >> ignore;
    }
  }
  else
  {
    periodStream >> ignore;
  }
  int weight;
  periodStream >> weight;
  periodStream >> ignore;
  date requestDate = from_simple_string(requestDateStr);
  cout << requestDate << ", " << shiftType << ", " << weight << endl;
  if (on)
  {
    this->shiftOnRequest[shiftType].push_back(make_pair(requestDate, weight));
  }
  else
  {
    this->shiftOffRequest[shiftType].push_back(make_pair(requestDate, weight));
  }
  return;
}
