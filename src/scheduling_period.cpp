#include "scheduling_period.hpp"


using namespace std;
using namespace boost::gregorian;
using namespace boost::posix_time;

bool SchedulingPeriod::Load(string periodFilePath)
{
  cout << "Scheduling period file path: " << periodFilePath << endl;
  ifstream periodStream(periodFilePath);
  if (periodStream.is_open())
  {
    this->LoadFromStream(periodStream);
    periodStream.close();
    return true;
  }
  else
  {
    cerr << "Unable to open scheduling period file." << endl;
    return false;
  }
}

void SchedulingPeriod::LoadFromStream(ifstream &periodStream)
{
  cout << "Scheduling period params:" << endl;
  cout << "#############################################################" << endl;
  while (!periodStream.eof())
  {
    string param;
    periodStream >> param;
    if (param == "SCHEDULING_PERIOD;")
    {
      this->LoadPeriod(periodStream);
    }
    if (param == "SHIFT_TYPES")
    {
      this->LoadShiftTypes(periodStream);
    }
  }
  cout << "#############################################################" << endl;
  cout << endl;
  cout << endl;
  return;
}

void SchedulingPeriod::LoadPeriod(ifstream &periodStream)
{
  string ignore;
  string tmpDate;
  periodStream >> ignore;
  periodStream >> this->name;
  this->name.pop_back();
  cout << "name: " << this->name << endl;
  periodStream >> tmpDate;
  tmpDate.pop_back();
  this->startDate = from_simple_string(tmpDate);
  cout << "start date: " << this->startDate << endl;
  periodStream >> tmpDate;
  tmpDate.pop_back();
  this->endDate = from_simple_string(tmpDate);
  cout << "end date: " << this->endDate << endl;
}

void SchedulingPeriod::LoadShiftTypes(ifstream &periodStream)
{
  string ignore;
  char ignoreChar;
  int numberOfTypes;
  char type;
  periodStream >> ignore;
  periodStream >> numberOfTypes;
  periodStream >> ignore;
  periodStream >> ignore;
  cout << endl;
  cout << "Shift types" << endl;
  for (int i = 0; i < numberOfTypes; ++i)
  {
    periodStream >> type;
    cout << type << ", ";
    periodStream >> ignore;
    periodStream >> ignore;
    if (type == 'D')
    {
      periodStream >> ignore;
    }
    string startTimeString;
    string endTimeString;
    periodStream >> startTimeString;
    periodStream >> endTimeString;
    startTimeString.pop_back();
    endTimeString.pop_back();
    time_duration startTime;
    time_duration endTime;
    startTime = duration_from_string(startTimeString);
    endTime = duration_from_string(endTimeString);
    this->shiftTypes[type] = make_pair(startTime, endTime);
    cout << this->shiftTypes[type].first << ", ";
    cout << this->shiftTypes[type].second << endl;
    periodStream >> ignore;
    periodStream >> ignore;
  }
}
