#ifndef NEIGHBOURHOOD_HPP
#define NEIGHBOURHOOD_HPP

#include <string>
#include <vector>
#include <map>
#include <iostream>

#include "roster.hpp"

class Neighbourhood
{
  public:
    Neighbourhood(){};
    Roster MoveNeighbourhoodStructure(Roster roster);
    Roster SwapNeighbourhoodStructure(Roster roster);
    Roster SwapPatternOfShifts(Roster roster);
    Roster TokenRingMove(Roster roster);
    ~Neighbourhood(){}
};

#endif
