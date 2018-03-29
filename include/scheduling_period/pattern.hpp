#ifndef PATTERN_HPP
#define PATTERN_HPP

#include <string>
#include <vector>
#include <utility>
#include <fstream>
#include <iostream>

#include "scheduling_period/constrain.hpp"


class Pattern
{
  public:
    Pattern(){};
    void LoadFromStream(std::ifstream &filtersStream);
    int id;
    int weight;
    std::vector<std::pair<std::string, std::string>> shifts;
    ~Pattern(){}
  private:
    Constrain LoadShift(std::ifstream &periodStream);

};

#endif
