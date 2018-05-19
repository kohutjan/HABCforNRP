#include "HABC.hpp"

using namespace std;
using namespace boost::gregorian;

void HABC::PrintStats(string mode, int max, int outputFrequency)
{
  cout << "------------------------------" << endl;
  cout << "Mode: " << mode << endl;
  cout << "SN: " << this->SN << endl;
  cout << "limit: " << this->limit << endl;
  cout << "HCR: " << this->HCR << endl;
  cout << "Max: " << max << endl;
  cout << "Output frequency: " << outputFrequency << endl;
  cout << "------------------------------" << endl;
}

void HABC::RunRostersLimit(int rostersLimit, int outputFrequency)
{
  this->PrintStats("Roster", rostersLimit, outputFrequency);
  int freq = outputFrequency;
  this->generatedRosters = 0;
  this->InitFood();
  while(rostersLimit > this->generatedRosters)
  {
    if (this->generatedRosters > freq)
    {
      freq = this->generatedRosters + outputFrequency;
      cout << this->bestRoster.penalty << endl;
    }
    if (this->hillClimbing)
    {
      if (this->prob)
      {
        this->SendEmployedBeesWithHillClimbingProb();
      }
      else
      {
        this->SendEmployedBeesWithHillClimbing();
      }
    }
    else
    {
      this->SendEmployedBees();
    }
    this->SendOnlookerBees();
    this->SendScoutBees();
  }
  cout << this->bestRoster.penalty << endl;
}

void HABC::RunIter(int iterations, int outputFrequency)
{
  this->PrintStats("Iteration", iterations, outputFrequency);
  this->InitFood();
  for (int i = 0; i < iterations; ++i)
  {
    if (i % outputFrequency == 0)
    {
      cout << this->bestRoster.penalty << endl;
    }
    if (this->hillClimbing)
    {
      if (this->prob)
      {
        this->SendEmployedBeesWithHillClimbingProb();
      }
      else
      {
        this->SendEmployedBeesWithHillClimbing();
      }
    }
    else
    {
      this->SendEmployedBees();
    }
    this->SendOnlookerBees();
    this->SendScoutBees();
  }
  cout << this->bestRoster.penalty << endl;
}

void HABC::Run()
{
  this->PrintStats("Time", this->timeToSolve.count() / 1000, this->outputFrequency.count() / 1000);
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
      if (this->prob)
      {
        this->SendEmployedBeesWithHillClimbingProb();
      }
      else
      {
        this->SendEmployedBeesWithHillClimbing();
      }
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


void HABC::InitFood()
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
  this->generatedRosters += this->SN;
  for (auto& roster: this->rosters)
  {
    roster.penalty = this->objectiveFunction.Forward(roster);
  }
  this->SortRosters();
  this->bestRoster = this->rosters[0];
  cout << this->bestRoster.penalty << endl;
  return;
}


void HABC::SortRosters()
{
  sort( this->rosters.begin( ), this->rosters.end( ), [&]( const Roster& roster1, const Roster& roster2 )
  {
    return roster1.penalty < roster2.penalty;
  });
  return;
}


void HABC::SendEmployedBeesWithHillClimbing()
{
  random_device rd;
  mt19937 eng(rd());
  std::uniform_real_distribution<> dis(0.0, 1.0);
  bool newRosterSet = false;
  for (auto& roster: this->rosters)
  {
    if (dis(eng) <= this->HCR)
    {
      while(1)
      {
        /*
        Roster newRoster;
        newRoster = this->ApplyRandomNeighbourhood(roster);
        newRoster.penalty = this->objectiveFunction.Forward(newRoster);
        if (newRoster.penalty < roster.penalty)
        {
          roster = newRoster;
          newRosterSet = true;
        }
        else
        {
          break;
        }
        */


        Roster moveRoster = this->neighbourhood.MoveNeighbourhoodStructure(roster);
        moveRoster.penalty = this->objectiveFunction.Forward(moveRoster);
        Roster swapRoster = this->neighbourhood.SwapNeighbourhoodStructure(roster);
        swapRoster.penalty = this->objectiveFunction.Forward(swapRoster);
        Roster patternRoster = this->neighbourhood.SwapPatternOfShifts(roster);
        patternRoster.penalty = this->objectiveFunction.Forward(patternRoster);
        Roster tokenRoster = this->neighbourhood.TokenRingMove(roster);
        tokenRoster.penalty = this->objectiveFunction.Forward(tokenRoster);
        this->generatedRosters += 4;
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
          newRosterSet = true;
        }
        else
        {
          break;
        }
      }
      if (not newRosterSet)
      {
        ++roster.trial;
      }
    }
  }
  return;
}


void HABC::SendEmployedBeesWithHillClimbingProb()
{
  random_device rd;
  mt19937 eng(rd());
  std::uniform_real_distribution<> dis(0.0, 1.0);
  bool newRosterSet = false;
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
        this->generatedRosters += 4;
        int rulInterval = 0;
        int moveStart = 10000;
        int moveEnd = 10000;
        int swapStart = 10000;
        int swapEnd = 10000;
        int patternStart = 10000;
        int patternEnd = 10000;
        int tokenStart = 10000;
        int tokenEnd = 10000;
        if (moveRoster.penalty < roster.penalty)
        {
          moveStart = rulInterval;
          rulInterval += 8;
          moveEnd = rulInterval;
        }
        if (swapRoster.penalty < roster.penalty)
        {
          swapStart = rulInterval;
          rulInterval += 2;
          swapEnd = rulInterval;
        }
        if (patternRoster.penalty < roster.penalty)
        {
          patternStart = rulInterval;
          rulInterval += 8;
          patternEnd = rulInterval;
        }
        if (tokenRoster.penalty < roster.penalty)
        {
          tokenStart = rulInterval;
          rulInterval += 2;
          tokenEnd = rulInterval;
        }
        if (rulInterval > 0)
        {
          int rul = this->neighbourhood.GetRandom(0, rulInterval - 1);
          if (moveStart <= rul && rul < moveEnd)
          {
            roster = moveRoster;
          }
          if (swapStart <= rul && rul < swapEnd)
          {
            roster = swapRoster;
          }
          if (patternStart <= rul && rul < patternEnd)
          {
            roster = patternRoster;
          }
          if (tokenStart <= rul && rul < tokenEnd)
          {
            roster = tokenRoster;
          }
          newRosterSet = true;
        }
        else
        {
          break;
        }
      }
      if (not newRosterSet)
      {
        ++roster.trial;
      }
    }
  }
  return;
}


void HABC::SendEmployedBees()
{
  for (auto& roster: this->rosters)
  {
    Roster newRoster;
    if (this->prob)
    {
      newRoster = this->ApplyRandomNeighbourhoodProb(roster);
    }
    else
    {
      newRoster = this->ApplyRandomNeighbourhood(roster);
    }
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


Roster HABC::ApplyRandomNeighbourhood(Roster& roster)
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
  ++this->generatedRosters;
  return newRoster;
}


Roster HABC::ApplyRandomNeighbourhoodProb(Roster& roster)
{
  int rul = this->neighbourhood.GetRandom(0, 19);
  Roster newRoster;
  if (0 <= rul && rul < 8)
  {
    newRoster = this->neighbourhood.MoveNeighbourhoodStructure(roster);
  }
  if (8 <= rul && rul < 10)
  {
    newRoster = this->neighbourhood.SwapNeighbourhoodStructure(roster);
  }
  if (10 <= rul && rul < 18)
  {
    newRoster = this->neighbourhood.SwapPatternOfShifts(roster);
  }
  if (18 <= rul && rul < 20)
  {
    newRoster = this->neighbourhood.TokenRingMove(roster);
  }
  ++this->generatedRosters;
  return newRoster;
}


void HABC::SendOnlookerBees()
{
  for (int i = 0; i < this->SN; ++i)
  {
    random_device rd;
    mt19937 eng(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    float r = dis(eng);
    int j = 0;
    float sumProb = 0;
    float penaltySum = 0;
    for (auto& roster: this->rosters)
    {
      penaltySum += roster.penalty;
    }
    vector<float> probVals(this->rosters.size());
    for (size_t j = 0; j < this->rosters.size(); ++j)
    {
      probVals[j] = this->rosters[j].penalty / penaltySum;
    }
    vector<int> rostersIndexes(probVals.size());
    size_t n(0);
    generate(begin(rostersIndexes), end(rostersIndexes), [&]{ return n++; });
    sort(begin(rostersIndexes), end(rostersIndexes),
         [&](int i1, int i2) { return probVals[i1] < probVals[i2]; } );
    vector<float> rulVals(this->rosters.size());
    for (size_t j = 0; j < this->rosters.size(); ++j)
    {
      rulVals[rostersIndexes[this->rosters.size() - j - 1]] = probVals[rostersIndexes[j]];
    }


    while (j < this->SN)
    {
      //sumProb += this->rosters[j].penalty / penaltySum;
      sumProb += rulVals[j];
      if (sumProb > r)
      {
        break;
      }
      else
      {
        ++j;
      }
    }
    //cout << "R: " << r << endl;
    //cout << "Sum prob: " << sumProb << endl;
    //cout << "Onlooker pick: ";
    //cout << this->rosters[i].penalty << endl;
    Roster newRoster;
    if (this->prob)
    {
      newRoster = this->ApplyRandomNeighbourhoodProb(this->rosters[j]);
    }
    else
    {
      newRoster = this->ApplyRandomNeighbourhood(this->rosters[j]);
    }
    newRoster.penalty = this->objectiveFunction.Forward(newRoster);
    if (newRoster.penalty < this->rosters[j].penalty)
    {
      this->rosters[j] = newRoster;
    }
    else
    {
      ++this->rosters[j].trial;
    }
  }
  return;
}


void HABC::SendScoutBees()
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
    ++this->generatedRosters;
  }
  return;
}


void HABC::SaveSolution(string pathToOuptutFile)
{
  if (pathToOuptutFile.empty())
  {
    return;
  }
  ofstream outputStream(pathToOuptutFile);
  Roster randomRoster;
  randomRoster.Init(this->schedulingPeriod.startDate, this->schedulingPeriod.endDate,
                    this->schedulingPeriod.employees, this->schedulingPeriod.shifts,
                    this->schedulingPeriod.dayOfWeekCover,
                    this->schedulingPeriod.dateSpecificCover);
  outputStream << this->bestRoster.table << endl;
  outputStream << endl;
  this->objectiveFunction.Forward(this->bestRoster);
  this->objectiveFunction.SaveOutput(outputStream);
  outputStream << endl;
  outputStream << "Solution: " << this->bestRoster.penalty << endl;
  int randomPenalty = this->objectiveFunction.Forward(randomRoster);
  outputStream << "Random solution: " << randomPenalty << endl;
  outputStream << endl;
  outputStream.close();
  cout << endl;
  cout << "Solution was saved to: " << pathToOuptutFile << endl;
  return;
}


void HABC::SaveSolutionToXML(string pathToOuptutFile)
{
  if (pathToOuptutFile.empty())
  {
    return;
  }
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
        outputStream << "<ShiftType>" << shiftTypeStr << "</ShiftType>" << endl;
        outputStream << "</Assignment>" << endl;
      }
    }
  }
  outputStream << "</Solution>" << endl;
  outputStream.close();
  cout << endl;
  cout << "Solution was saved to: " << pathToOuptutFile << endl;
  return;
}
