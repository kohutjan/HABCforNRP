#include "HBAC.hpp"

using namespace std;

void HBAC::InitRosters()
{
  for (int i = 0; i < this->SN; ++i)
  {
    Roster roster;
    roster.Init(this->schedulingPeriod.startDate, this->schedulingPeriod.endDate,
                this->schedulingPeriod.employees, this->schedulingPeriod.shifts,
                this->schedulingPeriod.dayOfWeekCover,
                this->schedulingPeriod.dateSpecificCover);
    this->rosters.push_back(roster);
  }
  sort( this->rosters.begin( ), this->rosters.end( ), [&]( const Roster& roster1, const Roster& roster2 )
  {
    return this->objectiveFunction.Forward(roster1) < this->objectiveFunction.Forward(roster2);
  });
}

void HBAC::ApplyNeighbourhood()
{
  for (int i = 0; i < this->SN; ++i)
  {
    int neighbourhoodIndex = this->neighbourhood.GetRandomNeighbourhood();
    Roster newRoster;
    switch (neighbourhoodIndex)
    {
      case MNS:
        newRoster = this->neighbourhood.MoveNeighbourhoodStructure(this->rosters[i]);
        break;

      case SNS:
        newRoster = this->neighbourhood.SwapNeighbourhoodStructure(this->rosters[i]);
        break;

      case SPS:
        newRoster = this->neighbourhood.SwapPatternOfShifts(this->rosters[i]);
        break;

      case TRM:
        newRoster = this->neighbourhood.TokenRingMove(this->rosters[i]);
        break;

      default:
        break;
    }
    if (this->CompareRosters(newRoster, this->rosters[i]))
    {
      this->rosters[i] = newRoster;
    }
    else
    {
      ++this->rosters[i].trial;
    }
  }
}


bool HBAC::CompareRosters(Roster& roster1, Roster& roster2)
{
  return (this->objectiveFunction.Forward(roster1) < this->objectiveFunction.Forward(roster2));
}


void HBAC::TestRosters()
{
  int index = 0;
  ObjectiveFunction objectiveFunction(this->schedulingPeriod);
  Neighbourhood neighbourhood;
  for (auto& roster: this->rosters)
  {
    int penalty = objectiveFunction.Forward(roster);
    Roster newRoster = neighbourhood.TokenRingMove(roster);
    newRoster = neighbourhood.MoveNeighbourhoodStructure(roster);
    newRoster = neighbourhood.SwapNeighbourhoodStructure(roster);
    newRoster = neighbourhood.SwapPatternOfShifts(roster);
    int newPenalty = objectiveFunction.Forward(newRoster);
    //roster.Print();
    cout << endl;
    cout << endl;
    cout << "Objective function output for roster " << index << ": " << penalty;
    cout << endl;
    cout << endl;
    //newRoster.Print();
    cout << endl;
    cout << endl;
    cout << "Objective function output for new roster " << index << ": " << newPenalty;
    cout << endl;
    cout << endl;
    ++index;
  }
}
