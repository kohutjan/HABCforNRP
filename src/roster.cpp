#include "roster.hpp"

using namespace std;
using namespace boost::gregorian;
using namespace Eigen;

void Roster::Init(date startDate, date endDate,
                  map<int, Employee> employees, map<char, Shift> shifts,
                  map<char, map<char, int>> dayOfWeekCover,
                  map<string, map<char, int>> dateSpecificCover)
{
  for(auto& employee: employees)
  {
    this->employeeIds.push_back(employee.first);
  }
  date_duration rosterDuration = endDate - startDate;
  sort(this->employeeIds.begin(), this->employeeIds.end());
  int dayIndex = 0;
  for(day_iterator iter = startDate; iter != (endDate + days(1)); ++iter)
  {
    this->dates.push_back(*iter);
    this->daysOfWeek.push_back(GregToDay(iter->day_of_week()));
    if ((iter->day_of_week() == boost::date_time::Saturday) &
       ((dayIndex + 1) < (rosterDuration.days() + 1)))
    {
      this->SSWeekendIndexes.push_back(dayIndex);
    }
    if ((iter->day_of_week() == boost::date_time::Friday) &
       ((dayIndex + 2) < (rosterDuration.days() + 1)))
    {
      this->FSSWeekendIndexes.push_back(dayIndex);
    }
    ++dayIndex;
  }
  this->table = Matrix<char, Dynamic, Dynamic>::Constant(employees.size(),
                                                         rosterDuration.days() + 1,
                                                         NONE);
  this->InitSumOfDemands(shifts, dayOfWeekCover);
  this->InitShiftOrdering();
  for (auto& shiftType: this->shiftOrdering)
  {
    this->AssignShift(shiftType, dayOfWeekCover, dateSpecificCover);
  }
}

void Roster::AssignShift(char shiftType, map<char, map<char, int>> dayOfWeekCover,
                         map<string, map<char, int>> dateSpecificCover)
{
  for (size_t dateIndex = 0; dateIndex < this->dates.size(); ++dateIndex)
  {
    int dateCover;
    dateCover = this->GetDateCover(this->dates[dateIndex], shiftType, dateSpecificCover);
    if (dateCover != NOT_FOUND)
    {
      this->AssignShiftToDate(dateIndex, shiftType, dateCover);
    }
    else
    {
      int dayCover;
      dayCover = this->GetDayCover(dateIndex, shiftType, dayOfWeekCover);
      if (dayCover != NOT_FOUND && dayCover != 0)
      {
        this->AssignShiftToDate(dateIndex, shiftType, dayCover);
      }
    }
  }
}

void Roster::AssignShiftToDate(int dateIndex, char shiftType, int cover)
{
  if (cover == 0)
  {
    return;
  }

  vector<int> freeEmployeesIndexes;
  random_device rd;
  mt19937 eng(rd());

  for (int i = 0; i < this->table.rows(); ++i)
  {
    if (this->table.col(dateIndex)[i] == NONE)
    {
      freeEmployeesIndexes.push_back(i);
    }
  }
  size_t numberOfFreeEmployees = freeEmployeesIndexes.size();
  for (size_t i = 0; i < numberOfFreeEmployees; i++)
  {
    uniform_int_distribution<> distr(0, numberOfFreeEmployees - i - 1);
    int j = distr(eng);
    if (j != 0)
    {
      swap(freeEmployeesIndexes[i], freeEmployeesIndexes[i + j]);
    }
  }
  for (int i = 0; i < cover; ++i)
  {
    this->table.col(dateIndex)[freeEmployeesIndexes[i]] = shiftType;
  }
}

int Roster::GetDateCover(date specificDate, char shiftType, map<string, map<char, int>> dateSpecificCover)
{
  for (auto& dateCover: dateSpecificCover)
  {
    if (from_simple_string(dateCover.first) == specificDate)
    {
      if (dateCover.second.count(shiftType) > 0)
      {
        return dateCover.second[shiftType];
      }
    }
  }
  return NOT_FOUND;
}

int Roster::GetDayCover(int dateIndex, char shiftType, map<char, map<char, int>> dayOfWeekCover)
{
  for (auto& dayCover: dayOfWeekCover)
  {
    if (this->daysOfWeek[dateIndex] == dayCover.first)
    {
      if (dayCover.second.count(shiftType) > 0)
      {
        return dayCover.second[shiftType];
      }
    }
  }
  return NOT_FOUND;
}

void Roster::InitSumOfDemands(map<char, Shift> shifts,
                              map<char, map<char, int>> dayOfWeekCover)
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
  cout << "Matrix dimension: " <<  this->table.rows() << ", " << this->table.cols() << endl;
  cout << endl;
  cout << endl;
  cout << "SaturdaySunday indexes" << endl;
  for (auto& indexDay: this->SSWeekendIndexes)
  {
    cout << indexDay << " ";
  }
  cout << endl;
  cout << endl;
  cout << "FridaySaturdaySunday indexes" << endl;
  for (auto& indexDay: this->FSSWeekendIndexes)
  {
    cout << indexDay << " ";
  }
  cout << endl;
  cout << endl;
  cout << this->table << endl;
  cout << endl;
}
