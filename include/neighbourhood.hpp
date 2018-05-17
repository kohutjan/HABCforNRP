#ifndef NEIGHBOURHOOD_HPP
#define NEIGHBOURHOOD_HPP

#define MNS 0
#define SNS 1
#define SPS 2
#define TRM 3

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <random>

#include "roster.hpp"
#include "scheduling_period.hpp"

typedef Eigen::DenseBase<Eigen::Matrix<char, -1, -1>>::RowXpr Row;
typedef Eigen::DenseBase<Eigen::Matrix<char, -1, -1>>::ColXpr Col;

class Neighbourhood
{
  public:
    Neighbourhood(){}
    Neighbourhood(SchedulingPeriod _schedulingPeriod) : schedulingPeriod(_schedulingPeriod){}
    Roster MoveNeighbourhoodStructure(Roster roster);
    Roster SwapNeighbourhoodStructure(Roster roster);
    Roster SwapPatternOfShifts(Roster roster);
    Roster TokenRingMove(Roster roster);
    int GetRandomNeighbourhood();
    int GetRandom(int start, int end);
    void setPrint() { print = true; }
    ~Neighbourhood(){}
  private:
    SchedulingPeriod schedulingPeriod;
    bool CheckAndSwapPattern(int colIndex, int sizeOfPattern, Row firstEmployeesShifts,
                             Row secondEmployeesShifts);
    std::vector<int> GetNoneShiftIndexes(Col dayShifts);
    std::vector<int> GetNoneShiftIndexes(Roster &roster, int colIndex);
    std::vector<int> GetAnyShiftIndexes(Col dayShifts);
    std::vector<int> GetAnyShiftIndexesWithoutSpecific(Col dayShifts, char shiftType);
    std::vector<int> GetRandomIndexes(int numberOfIndexes, int numberOfRandom);
    bool print = false;

};

#endif
