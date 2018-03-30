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
  cout << this->contractId << endl;
  periodStream >> ignore;
  periodStream >> ignore;
  periodStream >> ignore;
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
  periodStream >> ignore;
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
