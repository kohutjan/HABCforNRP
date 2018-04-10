#ifndef PATTERN_HPP
#define PATTERN_HPP

#include <string>
#include <vector>
#include <utility>
#include <fstream>
#include <iostream>

#include "scheduling_period/days.hpp"
#include "scheduling_period/shift.hpp"

class Pattern
{
  public:
    Pattern(){};
    void LoadFromStream(std::ifstream &periodStream);
    int id;
    int weight;
    std::vector<std::pair<char, char>> shifts;
    ~Pattern(){}
  private:
    void LoadShift(std::ifstream &periodStream);

};

#endif
