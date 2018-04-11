#include "HBAC.hpp"

using namespace std;


void HBAC::InitFood()
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
  for (auto& roster: this->rosters)
  {
    roster.penalty = this->objectiveFunction.Forward(roster);
  }
}


void HBAC::EmployedBees()
{
  for (auto& roster: this->rosters)
  {
    Roster newRoster;
    newRoster = this->ApplyRandomNeighbourhood(roster);
    newRoster.penalty = this->objectiveFunction.Forward(newRoster);
    //cout << "Old: " << roster.penalty << endl;
    //cout << "New: " << newRoster.penalty << endl;
    if (newRoster.penalty < roster.penalty)
    {
      roster = newRoster;
    }
    else
    {
      ++roster.trial;
    }
    //cout << "Picked: " << roster.penalty << endl;
    //cout << "Trial: " << roster.trial << endl;
    //cout << endl;
  }
}


Roster HBAC::ApplyRandomNeighbourhood(Roster& roster)
{
  int neighbourhoodIndex = this->neighbourhood.GetRandomNeighbourhood();
  Roster newRoster;
  switch (neighbourhoodIndex)
  {
    case MNS:
      newRoster = this->neighbourhood.MoveNeighbourhoodStructure(roster);
      break;

    case SNS:
      newRoster = this->neighbourhood.SwapNeighbourhoodStructure(roster);
      break;

    case SPS:
      newRoster = this->neighbourhood.SwapPatternOfShifts(roster);
      break;

    case TRM:
      newRoster = this->neighbourhood.TokenRingMove(roster);
      break;

    default:
      break;
  }
  return newRoster;
}


void HBAC::OnlookerBees()
{
  random_device rd;
  mt19937 eng(rd());
  std::uniform_real_distribution<> dis(0.0, 1.0);
  float r = dis(eng);
  int i = 0;
  float sumProb = 0;
  float penaltySum = 0;
  for (auto& roster: this->rosters)
  {
    penaltySum += roster.penalty;
  }
  while (i < this->SN)
  {
    sumProb += this->rosters[i].penalty / penaltySum;
    if (sumProb >= r)
    {
      break;
    }
    else
    {
      ++i;
    }
  }
  //cout << "R: " << r << endl;
  //cout << "Sum prob: " << sumProb << endl;
  //cout << "Onlooker pick: ";
  //cout << this->rosters[i].penalty << endl;
  Roster newRoster;
  newRoster = this->ApplyRandomNeighbourhood(this->rosters[i]);
  newRoster.penalty = this->objectiveFunction.Forward(newRoster);
  if (newRoster.penalty < this->rosters[i].penalty)
  {
    this->rosters[i] = newRoster;
  }
  else
  {
    ++this->rosters[i].trial;
  }
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
