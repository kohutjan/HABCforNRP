#ifndef HBAC_HPP
#define HBAC_HPP

#include <iostream>
#include <vector>
#include <eigen3/Eigen/Dense>
#include <chrono>

#include "scheduling_period.hpp"
#include "roster.hpp"
#include "objective_function.hpp"
#include "neighbourhood.hpp"


class HBAC
{
  public:
    HBAC(){}
    HBAC(int _SN, int _timeToSolve, int _limit, int _outputFrequency) :
         SN(_SN), limit(_limit)
    {
      hillClimbing = false;
      timeToSolve = std::chrono::milliseconds(_timeToSolve * 1000);
      outputFrequency = std::chrono::milliseconds(_outputFrequency * 1000);
    }
    HBAC(int _SN, int _timeToSolve, int _limit, float _HCR, int _outputFrequency) :
         SN(_SN), limit(_limit), HCR(_HCR)
    {
      hillClimbing = true;
      timeToSolve = std::chrono::milliseconds(_timeToSolve * 1000);
      outputFrequency = std::chrono::milliseconds(_outputFrequency * 1000);
    }
    void setSchedulingPeriod(SchedulingPeriod _schedulingPeriod)
    {
      schedulingPeriod = _schedulingPeriod;
      objectiveFunction = ObjectiveFunction(schedulingPeriod);
    }
    void Run();
    void SaveSolution(std::string pathToOuptutFile);
    void SaveSolutionToXML(std::string pathToOuptutFile);
    void TestRosters();
    ~HBAC(){}
  private:
    SchedulingPeriod schedulingPeriod;
    ObjectiveFunction objectiveFunction;
    Neighbourhood neighbourhood;
    int SN;
    std::chrono::duration<double, std::milli> timeToSolve;
    int limit;
    float HCR;
    std::chrono::duration<double, std::milli> outputFrequency;
    std::vector<Roster> rosters;
    Roster bestRoster;
    bool hillClimbing;
    void InitFood();
    void SendEmployedBeesWithHillClimbing();
    void SendEmployedBees();
    void SendOnlookerBees();
    void SendScoutBees();
    void SortRosters();
    Roster ApplyRandomNeighbourhood(Roster& roster);
};

#endif
