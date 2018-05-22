#include "neighbourhood.hpp"

using namespace std;

Roster Neighbourhood::MoveNeighbourhoodStructure(Roster roster)
{
  for (int i = 0; i < 20; ++i)
  {
    int randomColIndex = this->GetRandom(0, roster.table.cols() - 1);
    Col randomDayShifts = roster.table.col(randomColIndex);
    vector<int> noneShiftIndexes = this->GetNoneShiftIndexes(roster, randomColIndex);
    vector<int> anyShiftIndexes = this->GetAnyShiftIndexes(randomDayShifts);
    if (noneShiftIndexes.empty() || anyShiftIndexes.empty())
    {
      continue;
    }
    int randomNoneShiftIndex = this->GetRandom(0, noneShiftIndexes.size() - 1);
    int randomAnyShiftIndex = this->GetRandom(0, anyShiftIndexes.size() - 1);
    int firstIndex = noneShiftIndexes[randomNoneShiftIndex];
    int secondIndex = anyShiftIndexes[randomAnyShiftIndex];
    char firstShift = randomDayShifts[firstIndex];
    randomDayShifts[firstIndex] = randomDayShifts[secondIndex];
    randomDayShifts[secondIndex] = firstShift;
    if (this->print)
    {
      cout << endl;
      cout << "Col index: " << randomColIndex << endl;
      cout << "First index: " << firstIndex << endl;
      cout << "Second index: " << secondIndex << endl;
      cout << endl;
    }
    break;
  }
  return roster;
}


Roster Neighbourhood::SwapNeighbourhoodStructure(Roster roster)
{
  for (int i = 0; i < 20; ++i)
  {
    int randomColIndex = this->GetRandom(0, roster.table.cols() - 1);
    Col randomDayShifts = roster.table.col(randomColIndex);
    vector<int> anyShiftIndexes = this->GetAnyShiftIndexes(randomDayShifts);
    if (anyShiftIndexes.empty())
    {
      continue;
    }
    int randomAnyShiftIndex = this->GetRandom(0, anyShiftIndexes.size() - 1);
    int firstIndex = anyShiftIndexes[randomAnyShiftIndex];
    char firstShift = randomDayShifts[firstIndex];
    vector<int> anyShiftIndexesWithoutSpecific = this->GetAnyShiftIndexesWithoutSpecific(randomDayShifts, firstShift);
    if (anyShiftIndexesWithoutSpecific.empty())
    {
      continue;
    }
    int randomAnyShiftIndexWithoutSpecific = this->GetRandom(0, anyShiftIndexesWithoutSpecific.size() - 1);
    int secondIndex = anyShiftIndexesWithoutSpecific[randomAnyShiftIndexWithoutSpecific];
    randomDayShifts[firstIndex] = randomDayShifts[secondIndex];
    randomDayShifts[secondIndex] = firstShift;
    if (this->print)
    {
      cout << endl;
      cout << "Col index: " << randomColIndex << endl;
      cout << "First index: " << firstIndex << endl;
      cout << "Second index: " << secondIndex << endl;
      cout << endl;
    }
    break;
  }
  return roster;
}


Roster Neighbourhood::SwapPatternOfShifts(Roster roster)
{
  for (int i = 0; i < 20; ++i)
  {
    vector<int> randomRowIndexes = this->GetRandomIndexes(roster.table.rows(), 2);
    Row firstEmployeesShifts = roster.table.row(randomRowIndexes[0]);
    Row secondEmployeesShifts = roster.table.row(randomRowIndexes[1]);
    int randomSizeOfPattern = this->GetRandom(2, 5);
    int randomStartColIndex = this->GetRandom(0, roster.table.cols() - randomSizeOfPattern);
    int colIndex;
    bool patternFound = false;
    int direction = this->GetRandom(0, 1);
    if (direction)
    {
      for (int j = randomStartColIndex; j <= roster.table.cols() - randomSizeOfPattern; ++j)
      {
        patternFound = this->CheckAndSwapPattern(j, randomSizeOfPattern, firstEmployeesShifts, secondEmployeesShifts);
        if (patternFound)
        {
          colIndex = j;
          break;
        }
      }
    }
    else
    {
      for (int j = randomStartColIndex; j >= 0; --j)
      {
        patternFound = this->CheckAndSwapPattern(j, randomSizeOfPattern, firstEmployeesShifts, secondEmployeesShifts);
        if (patternFound)
        {
          colIndex = j;
          break;
        }
      }
    }
    if (patternFound)
    {
      if (this->print)
      {
        cout << endl;
        cout << "First row index: " << randomRowIndexes[0] << endl;
        cout << "Second row index: " << randomRowIndexes[1] << endl;
        cout << "Size of pattern: " << randomSizeOfPattern << endl;
        cout << "Col index: " << colIndex << endl;
        cout << "Direction: " << direction << endl;
        cout << "Start index: " << randomStartColIndex << endl;
        cout << endl;
      }
      break;
    }
  }
  return roster;
}


bool Neighbourhood::CheckAndSwapPattern(int colIndex, int sizeOfPattern,
                                        Row firstEmployeesShifts,
                                        Row secondEmployeesShifts)
{
  bool patternFound = true;
  bool identicalPattern = true;
  for (int k = 0; k < sizeOfPattern; ++k)
  {
    /*
    // Uncommet to have "none" type of pattern 
    bool brokenPattern = ((firstEmployeesShifts[colIndex + k] != NONE && secondEmployeesShifts[colIndex + k] == NONE) ||
                          (firstEmployeesShifts[colIndex + k] == NONE && secondEmployeesShifts[colIndex + k] != NONE));
    if (brokenPattern)
    {
      patternFound = false;
      break;
    }
    */

    if (firstEmployeesShifts[colIndex + k] != secondEmployeesShifts[colIndex + k])
    {
      identicalPattern = false;
    }
  }
  if (patternFound && !identicalPattern)
  {
    for (int s = colIndex; s < colIndex + sizeOfPattern; ++s)
    {
      char firstShift = firstEmployeesShifts[s];
      firstEmployeesShifts[s] = secondEmployeesShifts[s];
      secondEmployeesShifts[s] = firstShift;
    }
  }
  return (patternFound && !identicalPattern);
}


Roster Neighbourhood::TokenRingMove(Roster roster)
{
  for (int i = 0; i < 20; ++i)
  {
    int randomWeekendIndex = roster.SSWeekendIndexes[this->GetRandom(0, roster.SSWeekendIndexes.size() - 1)];
    Col saturday = roster.table.col(randomWeekendIndex);
    Col sunday = roster.table.col(randomWeekendIndex + 1);
    vector<int> saturdayNone;
    vector<int> sundayNone;
    for (int j = 0; j < saturday.size(); ++j)
    {
      if (saturday[j] == NONE && sunday[j] != NONE)
      {
        saturdayNone.push_back(j);
      }
      if (saturday[j] != NONE && sunday[j] == NONE)
      {
        sundayNone.push_back(j);
      }
    }
    if (not (saturdayNone.empty() || sundayNone.empty()))
    {
      int randomSaturdayNoneIndex = saturdayNone[this->GetRandom(0, saturdayNone.size() - 1)];
      int randomSundayNoneIndex = sundayNone[this->GetRandom(0, sundayNone.size() - 1)];
      saturday[randomSaturdayNoneIndex] = saturday[randomSundayNoneIndex];
      saturday[randomSundayNoneIndex] = NONE;

      if (this->print)
      {
        cout << endl;
        cout << "Weekend index: " << randomWeekendIndex << endl;
        cout << "Saturday none index: " << randomSaturdayNoneIndex << endl;
        cout << "Sunday none index: " << randomSundayNoneIndex << endl;
      }
    }

    vector<int> saturdaySunday;
    for (int j = 0; j < saturday.size(); ++j)
    {
      if (saturday[j] != NONE && sunday[j] != NONE)
      {
        saturdaySunday.push_back(j);
      }
    }
    if (saturdaySunday.size() < 2)
    {
      continue;
    }
    int firstWeekend;
    int secondWeekend;
    for (size_t j = 0; j < saturdaySunday.size(); ++j)
    {
      int firstWeekendIndex = saturdaySunday[j];
      for (size_t k = j + 1; k < saturdaySunday.size(); ++k)
      {
        int secondWeekendIndex = saturdaySunday[k];
        if ((saturday[firstWeekendIndex] == sunday[secondWeekendIndex] ||
            saturday[secondWeekendIndex] == sunday[firstWeekendIndex]) &&
            saturday[firstWeekendIndex] != sunday[firstWeekendIndex])
        {
          char sundayFirstShift = sunday[firstWeekendIndex];
          sunday[firstWeekendIndex] = sunday[secondWeekendIndex];
          sunday[secondWeekendIndex] = sundayFirstShift;
          firstWeekend = firstWeekendIndex;
          secondWeekend = secondWeekendIndex;
          break;
        }
      }
    }
    if (this->print)
    {
      cout << "First weekend index: " << firstWeekend << endl;
      cout << "Second weekend index: " << secondWeekend << endl;
      cout << endl;
    }
    break;
  }
  return roster;
}


vector<int> Neighbourhood::GetNoneShiftIndexes(Col dayShifts)
{
  vector<int> noneShiftIndexes;
  for (int i = 0; i < dayShifts.size(); ++i)
  {
    if (dayShifts[i] == NONE)
    {
      noneShiftIndexes.push_back(i);
    }
  }
  return noneShiftIndexes;
}


// Get none shift indexes with respect to day off request
vector<int> Neighbourhood::GetNoneShiftIndexes(Roster &roster, int colIndex)
{

  Col dayShifts = roster.table.col(colIndex);
  vector<int> noneShiftIndexes;
  for (int i = 0; i < dayShifts.size(); ++i)
  {
    Employee employee = this->schedulingPeriod.employees[roster.employeeIds[i]];
    bool workingDay = true;
    for (auto& dayOffRequest: employee.dayOffRequest)
    {
      if (dayOffRequest.first == roster.dates[colIndex])
      {
        workingDay = false;
      }
    }
    if (workingDay && dayShifts[i] == NONE)
    {
      noneShiftIndexes.push_back(i);
    }
  }
  return noneShiftIndexes;
}

vector<int> Neighbourhood::GetAnyShiftIndexes(Col dayShifts)
{
  vector<int> anyShiftIndexes;
  for (int i = 0; i < dayShifts.size(); ++i)
  {
    if (dayShifts[i] != NONE)
    {
      anyShiftIndexes.push_back(i);
    }
  }
  return anyShiftIndexes;
}


vector<int> Neighbourhood::GetAnyShiftIndexesWithoutSpecific(Col dayShifts, char shiftType)
{
  vector<int> anyShiftIndexesWithoutSpecific;
  for (int i = 0; i < dayShifts.size(); ++i)
  {
    if (dayShifts[i] != NONE && dayShifts[i] != shiftType)
    {
      anyShiftIndexesWithoutSpecific.push_back(i);
    }
  }
  return anyShiftIndexesWithoutSpecific;
}

// Returns vector of random indexes from range 0 to numberOfRandom
vector<int> Neighbourhood::GetRandomIndexes(int numberOfIndexes, int numberOfRandom)
{
  vector<int> v(numberOfIndexes);
  iota(begin(v), end(v), 0);

  random_device rd;
  mt19937 eng(rd());
  for (size_t i = 0; i < v.size(); i++)
  {
    uniform_int_distribution<> distr(0, v.size() - i - 1);
    int j = distr(eng);
    if (j != 0)
    {
      swap(v[i], v[i + j]);
    }
  }
  vector<int> randomSub(&v[0],&v[numberOfRandom]);
  return randomSub;
}


int Neighbourhood::GetRandom(int start, int end)
{
  random_device rd;
  mt19937 eng(rd());
  uniform_int_distribution<> distr(start, end);
  return distr(eng);
}

int Neighbourhood::GetRandomNeighbourhood()
{
  return this->GetRandom(MNS, TRM);
}
