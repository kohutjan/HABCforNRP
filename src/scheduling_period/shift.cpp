#include "scheduling_period/shift.hpp"


using namespace std;
using namespace boost::posix_time;


void Shift::LoadFromStream(ifstream &periodStream)
{
  string ignore;
  periodStream >> this->id;
  cout << this->id << ", ";
  periodStream >> ignore;
  periodStream >> ignore;
  if (this->id == 'D')
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
  cout << this->startTime << ", " << this->endTime << endl;
  periodStream >> ignore;
  periodStream >> ignore;
  return;
}
