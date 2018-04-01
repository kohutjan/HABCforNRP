#include "roster.hpp"

using namespace std;
using namespace boost::gregorian;
using namespace Eigen;

void Roster::Init(date startDate, date endDate,
                  map<int, Employee> employees, map<char, Shift> shifts,
                  map<string, map<char, int>> dayOfWeekCover,
                  map<string, map<char, int>> dateSpecificCover)
{
  for(auto& employee: employees)
  {
    this->employeeIds.push_back(employee.first);
  }
  sort(this->employeeIds.begin(), this->employeeIds.end());
  for(day_iterator iter = startDate; iter != (endDate + days(1)); ++iter)
  {
    this->dates.push_back(*iter);
    this->daysOfWeek.push_back(iter->day_of_week());
  }
  date_duration rosterDuration = endDate - startDate;
  this->table = Matrix<char, Dynamic, Dynamic>::Constant(employees.size(),
                                                         rosterDuration.days() + 1,
                                                         '-');
  this->InitSumOfDemands(shifts, dayOfWeekCover);
  this->InitShiftOrdering();
  this->AssignShift('N', dayOfWeekCover, dateSpecificCover);
  for (auto& shift: this->shiftOrdering)
  {
  }
}

void Roster::AssignShift(char shiftType, map<string, map<char, int>> dayOfWeekCover,
                         map<string, map<char, int>> dateSpecificCover)
{
  for (size_t i = 0; i < this->dates.size(); ++i)
  {
    map<char, int> dateCover;
    dateCover = this->GetDateCover(this->dates[i], dateSpecificCover);
    if (!dateCover.empty())
    {
      this->AssignShiftToDate(this->dates[i], shiftType, dateCover);
    }
    else
    {
      map<char, int> dayCover;
      dayCover = this->GetDayCover(this->dates[i], dayOfWeekCover);
      if (!dayCover.empty())
      {
        this->AssignShiftToDate(this->dates[i], shiftType, dayCover);
      }
    }
  }
}

void Roster::AssignShiftToDate(date specificDate, char shiftType, map<char, int> cover)
{
  
}

map<char, int> Roster::GetDateCover(date specificDate, map<string, map<char, int>> dateSpecificCover)
{

}

map<char, int> Roster::GetDayCover(date specificDate, map<string, map<char, int>> dateSpecificCover)
{

}

void Roster::InitSumOfDemands(map<char, Shift> shifts,
                              map<string, map<char, int>> dayOfWeekCover)
{
  for (auto& shift: shifts)
  {
    this->sumOfDemands[shift.first] = 0;
  }
  for (auto& cover: dayOfWeekCover)
  {
    for (auto& shift: cover.second)
    {
      this->sumOfDemands[shift.first] += shift.second;
    }
  }
}

void Roster::InitShiftOrdering()
{
  vector<int> sums;
  for (auto& demand: this->sumOfDemands)
  {
    sums.push_back(demand.second);
  }
  for (auto& sum: sums)
  {
    for (auto& demand: this->sumOfDemands)
    {
      if (demand.second == sum)
      {
        if (find(this->shiftOrdering.begin(),
                 this->shiftOrdering.end(), demand.first) == this->shiftOrdering.end())
        {
          this->shiftOrdering.push_back(demand.first);
        }
      }
    }
  }
}

void Roster::Print()
{
  cout << "Sum of demands" << endl;
  for (auto& demand: this->sumOfDemands)
  {
    cout << demand.first << ": " << demand.second << endl;
  }
  cout << endl;
  cout << endl;
  cout << "Shift ordering" << endl;
  for (auto& shift: this->shiftOrdering)
  {
    cout << shift << " ";
  }
  cout << endl;
  cout << endl;
  cout << this->table.rows() << ", " << this->table.cols() << endl;
  cout << this->table << endl;
  cout << endl;
}
