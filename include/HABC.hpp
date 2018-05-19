#ifndef HABC_HPP
#define HABC_HPP

#include <iostream>
#include <vector>
#include <eigen3/Eigen/Dense>
#include <chrono>

#include "scheduling_period.hpp"
#include "roster.hpp"
#include "objective_function.hpp"
#include "neighbourhood.hpp"


class HABC
{
  public:
    HABC(){}
    HABC(int _SN, int _timeToSolve, int _limit, int _outputFrequency, bool _prob) :
         SN(_SN), limit(_limit), prob(_prob)
    {
      hillClimbing = false;
      timeToSolve = std::chrono::milliseconds(_timeToSolve * 1000);
      outputFrequency = std::chrono::milliseconds(_outputFrequency * 1000);
    }
    HABC(int _SN, int _timeToSolve, int _limit, float _HCR, int _outputFrequency, bool _prob) :
         SN(_SN), limit(_limit), HCR(_HCR), prob(_prob)
    {
      hillClimbing = true;
      timeToSolve = std::chrono::milliseconds(_timeToSolve * 1000);
      outputFrequency = std::chrono::milliseconds(_outputFrequency * 1000);
    }
    HABC(int _SN, int _limit, bool _prob) : SN(_SN), limit(_limit), prob(_prob)
    {
      hillClimbing = false;
    }
    HABC(int _SN, int _limit, float _HCR, bool _prob) : SN(_SN), limit(_limit), HCR(_HCR), prob(_prob)
    {
      hillClimbing = true;
    }
    void setSchedulingPeriod(SchedulingPeriod _schedulingPeriod)
    {
      schedulingPeriod = _schedulingPeriod;
      neighbourhood = Neighbourhood(_schedulingPeriod);
      objectiveFunction = ObjectiveFunction(schedulingPeriod);
    }
    void Run();
    void RunIter(int iterations, int outputFrequency);
    void RunRostersLimit(int rostersLimit, int outputFrequency);
    void SaveSolution(std::string pathToOuptutFile);
    void SaveSolutionToXML(std::string pathToOuptutFile);
    void PrintStats(std::string mode, int max, int outputFrequency);
    ~HABC(){}
  private:
    SchedulingPeriod schedulingPeriod;
    ObjectiveFunction objectiveFunction;
    Neighbourhood neighbourhood;
    int SN;
    std::chrono::duration<double, std::milli> timeToSolve;
    int limit;
    float HCR;
    std::chrono::duration<double, std::milli> outputFrequency;
    int generatedRosters;
    std::vector<Roster> rosters;
    Roster bestRoster;
    bool hillClimbing;
    bool prob;
    void InitFood();
    void SendEmployedBeesWithHillClimbing();
    void SendEmployedBeesWithHillClimbingProb();
    void SendEmployedBees();
    void SendOnlookerBees();
    void SendScoutBees();
    void SortRosters();
    Roster ApplyRandomNeighbourhood(Roster& roster);
    Roster ApplyRandomNeighbourhoodProb(Roster& roster);
};

#endif
