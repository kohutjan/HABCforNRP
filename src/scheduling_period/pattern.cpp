#include "scheduling_period/pattern.hpp"


using namespace std;


void Pattern::LoadFromStream(ifstream &periodStream)
{
  string ignore;
  periodStream >> this->id;
  cout << this->id << ", ";
  periodStream >> ignore;
  periodStream >> this->weight;
  cout << this->weight << ", ";
  periodStream >> ignore;
  int numberOfShifts;
  periodStream >> numberOfShifts;
  for (int i = 0; i < numberOfShifts; ++i)
  {
    this->LoadShift(periodStream);
  }
  cout << endl;
  return;
}

void Pattern::LoadShift(ifstream &periodStream)
{
  char ignoreChar;
  periodStream >> ignoreChar;
  string shiftStr;
  periodStream >> shiftStr;
  shiftStr.pop_back();
  if (shiftStr.back() == ')')
  {
    shiftStr.pop_back();
  }
  int delimiterPos = shiftStr.find("|");
  string shiftType;
  string shiftDay;
  shiftType = shiftStr.substr(0, delimiterPos);
  if (shiftType == "DH")
  {
    shiftType = "H";
  }
  shiftDay = shiftStr.substr(delimiterPos + 1);
  cout << "(" << shiftType << "|" << shiftDay << ") ";
  this->shifts.push_back(make_pair(shiftType, shiftDay));
  return;
}
