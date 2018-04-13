#include "HBAC.hpp"

using namespace std;
using namespace boost::gregorian;

void HBAC::Run()
{
  auto startTime = chrono::high_resolution_clock::now();
  auto lastOutput = chrono::high_resolution_clock::now();
  this->InitFood();
  while(1)
  {
    auto actualTime = chrono::high_resolution_clock::now();
    auto actualDuration = actualTime - startTime;
    auto outputDuration = actualTime - lastOutput;
    if (actualDuration > this->timeToSolve)
    {
      break;
    }
    if (outputDuration > this->outputFrequency)
    {
      lastOutput = chrono::high_resolution_clock::now();
      cout << this->bestRoster.penalty << endl;
    }
    if (this->hillClimbing)
    {
      this->SendEmployedBeesWithHillClimbing();
    }
    else
    {
      this->SendEmployedBees();
    }
    this->SendOnlookerBees();
    this->SendScoutBees();
  }
  cout << this->bestRoster.penalty << endl;
  //this->objectiveFunction.setPrint();
  //this->objectiveFunction.Forward(this->bestRoster);
}


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
  for (auto& roster: this->rosters)
  {
    roster.penalty = this->objectiveFunction.Forward(roster);
  }
  this->SortRosters();
  this->bestRoster = this->rosters[0];
  cout << this->bestRoster.penalty << endl;
  return;
}


void HBAC::SortRosters()
{
  sort( this->rosters.begin( ), this->rosters.end( ), [&]( const Roster& roster1, const Roster& roster2 )
  {
    return roster1.penalty < roster2.penalty;
  });
  return;
}


void HBAC::SendEmployedBeesWithHillClimbing()
{
  random_device rd;
  mt19937 eng(rd());
  std::uniform_real_distribution<> dis(0.0, 1.0);
  for (auto& roster: this->rosters)
  {
    if (dis(eng) <= this->HCR)
    {
      while(1)
      {
        Roster moveRoster = this->neighbourhood.MoveNeighbourhoodStructure(roster);
        moveRoster.penalty = this->objectiveFunction.Forward(moveRoster);
        Roster swapRoster = this->neighbourhood.SwapNeighbourhoodStructure(roster);
        swapRoster.penalty = this->objectiveFunction.Forward(swapRoster);
        Roster patternRoster = this->neighbourhood.SwapPatternOfShifts(roster);
        patternRoster.penalty = this->objectiveFunction.Forward(patternRoster);
        Roster tokenRoster = this->neighbourhood.TokenRingMove(roster);
        tokenRoster.penalty = this->objectiveFunction.Forward(tokenRoster);
        vector<Roster> betterRosters;
        if (moveRoster.penalty < roster.penalty)
        {
          betterRosters.push_back(moveRoster);
        }
        if (swapRoster.penalty < roster.penalty)
        {
          betterRosters.push_back(swapRoster);
        }
        if (patternRoster.penalty < roster.penalty)
        {
          betterRosters.push_back(patternRoster);
        }
        if (tokenRoster.penalty < roster.penalty)
        {
          betterRosters.push_back(tokenRoster);
        }
        if (!betterRosters.empty())
        {
          int betterRosterIndex = this->neighbourhood.GetRandom(0, betterRosters.size() - 1);
          roster = betterRosters[betterRosterIndex];
        }
        else
        {
          break;
        }
      }
    }
  }
  return;
}


void HBAC::SendEmployedBees()
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
  return;
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


void HBAC::SendOnlookerBees()
{
  this->SortRosters();
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
  return;
}


void HBAC::SendScoutBees()
{
  this->SortRosters();
  if (this->rosters[0].penalty < this->bestRoster.penalty)
  {
    this->bestRoster = this->rosters[0];
  }
  int randomRosterIndex = this->neighbourhood.GetRandom(0, this->SN - 1);
  if (this->rosters[randomRosterIndex].trial >= limit)
  {
    Roster roster;
    roster.Init(this->schedulingPeriod.startDate, this->schedulingPeriod.endDate,
                this->schedulingPeriod.employees, this->schedulingPeriod.shifts,
                this->schedulingPeriod.dayOfWeekCover,
                this->schedulingPeriod.dateSpecificCover);
    roster.penalty = this->objectiveFunction.Forward(roster);
    this->rosters[randomRosterIndex] = roster;
  }
  return;
}


void HBAC::SaveSolution(string pathToOuptutFile)
{
  ofstream outputStream(pathToOuptutFile);
  outputStream << this->bestRoster.penalty << endl;
  outputStream << endl;
  outputStream << this->bestRoster.table << endl;
  outputStream.close();
}


void HBAC::SaveSolutionToXML(string pathToOuptutFile)
{
  ofstream outputStream(pathToOuptutFile);
  outputStream << "<Solution>" << endl;
  outputStream << "<SchedulingPeriodID>" << this->schedulingPeriod.id << "</SchedulingPeriodID>" << endl;
  outputStream << "<Competitor>xkohut08</Competitor>" << endl;
  outputStream << "<SoftConstraintsPenalty>" << this->bestRoster.penalty << "</SoftConstraintsPenalty>" << endl;
  for (int i = 0; i < this->bestRoster.table.rows(); ++i)
  {
    for (int j = 0; j < this->bestRoster.table.cols(); ++j)
    {
      char shiftType = this->bestRoster.table(i, j);
      if (shiftType != '-')
      {
        string shiftTypeStr;
        if (shiftType == 'H')
        {
          shiftTypeStr = "DH";
        }
        else
        {
          shiftTypeStr = shiftType;
        }
        outputStream << "<Assignment>" << endl;
        outputStream << "<Date>" << to_iso_extended_string(this->bestRoster.dates[j]) << "</Date>" << endl;
        outputStream << "<Employee>" << this->bestRoster.employeeIds[i] << "</Employee>" << endl;
        outputStream << "<ShiftType>" << shiftType << "</ShiftType>" << endl;
        outputStream << "</Assignment>" << endl;
      }
    }
  }
  outputStream << "</Solution>" << endl;
  outputStream.close();
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
