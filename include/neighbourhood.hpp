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

typedef Eigen::DenseBase<Eigen::Matrix<char, -1, -1>>::RowXpr Row;
typedef Eigen::DenseBase<Eigen::Matrix<char, -1, -1>>::ColXpr Col;

class Neighbourhood
{
  public:
    Neighbourhood(){};
    Roster MoveNeighbourhoodStructure(Roster roster);
    Roster SwapNeighbourhoodStructure(Roster roster);
    Roster SwapPatternOfShifts(Roster roster);
    Roster TokenRingMove(Roster roster);
    int GetRandomNeighbourhood();
    void setPrint() { print = true; }
    ~Neighbourhood(){}
  private:
    bool CheckAndSwapPattern(int colIndex, int sizeOfPattern, Row firstEmployeesShifts,
                             Row secondEmployeesShifts);
    std::vector<int> GetNoneShiftIndexes(Col dayShifts);
    std::vector<int> GetAnyShiftIndexes(Col dayShifts);
    std::vector<int> GetAnyShiftIndexesWithoutSpecific(Col dayShifts, char shiftType);
    std::vector<int> GetRandomIndexes(int numberOfIndexes, int numberOfRandom);
    int GetRandom(int start, int end);
    bool print = false;

};

#endif
