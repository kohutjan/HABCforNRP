#include "neighbourhood.hpp"

using namespace std;

Roster Neighbourhood::MoveNeighbourhoodStructure(Roster roster)
{
  for (int i = 0; i < 20; ++i)
  {
    int randomColIndex = this->GetRandom(0, roster.table.cols() - 1);
    Col randomDayShifts = roster.table.col(randomColIndex);
    vector<int> noneShiftIndexes = this->GetNoneShiftIndexes(randomDayShifts);
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
    cout << endl;
    cout << "Col index: " << randomColIndex << endl;
    cout << "First index: " << firstIndex << endl;
    cout << "Second index: " << secondIndex << endl;
    cout << endl;
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
    cout << endl;
    cout << "Col index: " << randomColIndex << endl;
    cout << "First index: " << firstIndex << endl;
    cout << "Second index: " << secondIndex << endl;
    cout << endl;
    break;
  }
  return roster;
}


Roster Neighbourhood::SwapPatternOfShifts(Roster roster)
{
  return roster;
}


Roster Neighbourhood::TokenRingMove(Roster roster)
{
  return roster;
}


vector<int> Neighbourhood::GetNoneShiftIndexes(Col dayShifts)
{
  vector<int> noneShiftIndexes;
  for (int i = 0; i < dayShifts.size(); ++i)
  {
    if(dayShifts[i] == NONE)
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
    if(dayShifts[i] != NONE)
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
    if(dayShifts[i] != NONE && dayShifts[i] != shiftType)
    {
      anyShiftIndexesWithoutSpecific.push_back(i);
    }
  }
  return anyShiftIndexesWithoutSpecific;
}


int Neighbourhood::GetRandom(int start, int end)
{
  random_device rd;
  mt19937 eng(rd());
  uniform_int_distribution<> distr(start, end);
  return distr(eng);
}
