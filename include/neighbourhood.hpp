#ifndef NEIGHBOURHOOD_HPP
#define NEIGHBOURHOOD_HPP

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <random>

#include "roster.hpp"

typedef Eigen::DenseBase<Eigen::Matrix<char, -1, -1>>::ColXpr Col;

class Neighbourhood
{
  public:
    Neighbourhood(){};
    Roster MoveNeighbourhoodStructure(Roster roster);
    Roster SwapNeighbourhoodStructure(Roster roster);
    Roster SwapPatternOfShifts(Roster roster);
    Roster TokenRingMove(Roster roster);
    ~Neighbourhood(){}
  private:
    std::vector<int> GetNoneShiftIndexes(Col dayShifts);
    std::vector<int> GetAnyShiftIndexes(Col dayShifts);
    std::vector<int> GetAnyShiftIndexesWithoutSpecific(Col dayShifts, char shiftType);
    int GetRandom(int start, int end);
};

#endif
