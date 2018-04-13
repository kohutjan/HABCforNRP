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
      cout << endl;
      cout << "Shifts" << endl;
      this->shifts = this->LoadParam<char, Shift>(periodStream);
    }
    if (param == "CONTRACTS")
    {
      cout << endl;
      cout << "Contracts" << endl;
      this->contracts = this->LoadParam<int, Contract>(periodStream);
    }
    if (param == "PATTERNS")
    {
      cout << endl;
      cout << "Patterns" << endl;
      this->patterns = this->LoadParam<int, Pattern>(periodStream);
    }
    if (param == "EMPLOYEES")
    {
      this->LoadEmployees(periodStream);
    }
    if (param == "DAY_OF_WEEK_COVER")
    {
      this->LoadCover(periodStream, true);
    }
    if (param == "DATE_SPECIFIC_COVER")
    {
      this->LoadCover(periodStream, false);
    }
    if (param == "DAY_OFF_REQUESTS")
    {
      this->LoadRequests(periodStream, false, true);
    }
    if (param == "DAY_ON_REQUESTS")
    {
      this->LoadRequests(periodStream, true, true);
    }
    if (param == "SHIFT_OFF_REQUESTS")
    {
      this->LoadRequests(periodStream, false, false);
    }
    if (param == "SHIFT_ON_REQUESTS")
    {
      this->LoadRequests(periodStream, true, false);
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
  periodStream >> this->id;
  this->id.pop_back();
  cout << this->id << ", ";
  periodStream >> tmpDate;
  tmpDate.pop_back();
  this->startDate = from_simple_string(tmpDate);
  cout << this->startDate << ", ";
  periodStream >> tmpDate;
  tmpDate.pop_back();
  this->endDate = from_simple_string(tmpDate);
  cout << this->endDate << endl;
  return;
}

void SchedulingPeriod::LoadEmployees(ifstream &periodStream)
{
  cout << endl;
  cout << "Employees" << endl;
  string ignore;
  int numberOfEmployees;
  periodStream >> numberOfEmployees;
  periodStream >> ignore;
  periodStream >> ignore;
  for (int i = 0; i < numberOfEmployees; ++i)
  {
    Employee employee;
    employee.LoadFromStream(periodStream);
    this->employees[employee.id] = employee;
  }
}


void SchedulingPeriod::LoadRequests(ifstream &periodStream, bool on, bool day)
{
  cout << endl;
  if (day)
  {
    cout << "Day ";
  }
  else
  {
    cout << "Shift ";
  }
  if (on)
  {
    cout << "on requests" << endl;
  }
  else
  {
    cout << "off requests" << endl;
  }
  string ignore;
  int numberOfRequests;
  periodStream >> ignore;
  periodStream >> numberOfRequests;
  periodStream >> ignore;
  periodStream >> ignore;
  int employeeId;
  for (int i = 0; i < numberOfRequests; ++i)
  {
    periodStream >> employeeId;
    periodStream >> ignore;
    cout << employeeId << ", ";
    if (day)
    {
      this->employees[employeeId].LoadDayRequest(periodStream, on);
    }
    else
    {
      this->employees[employeeId].LoadShiftRequest(periodStream, on);
    }
  }
}

void SchedulingPeriod::LoadCover(ifstream &periodStream, bool day)
{
  cout << endl;
  if (day)
  {
    cout << "Day of week cover" << endl;
  }
  else
  {
    cout << "Date specific cover" << endl;
  }
  string ignore;
  int numberOfCovers;
  periodStream >> ignore;
  periodStream >> numberOfCovers;
  periodStream >> ignore;
  periodStream >> ignore;
  for (int i = 0; i < numberOfCovers; ++i)
  {
    string dateDay;
    periodStream >> dateDay;
    dateDay.pop_back();
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
    int numberOfEmployees;
    periodStream >> numberOfEmployees;
    periodStream >> ignore;
    if (day)
    {
      char day = StrToDay(dateDay);
      this->dayOfWeekCover[day][shiftType] = numberOfEmployees;
      cout << dateDay << ", " << shiftType << ", ";
      cout << this->dayOfWeekCover[day][shiftType] << endl;
    }
    else
    {
      this->dateSpecificCover[dateDay][shiftType] = numberOfEmployees;
      cout << dateDay << ", " << shiftType << ", ";
      cout << this->dateSpecificCover[dateDay][shiftType] << endl;
    }
  }
  return;
}
