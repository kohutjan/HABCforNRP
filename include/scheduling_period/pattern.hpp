#ifndef PATTERN_HPP
#define PATTERN_HPP

#include <string>
#include <vector>
#include <utility>
#include <fstream>
#include <iostream>


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
    void LoadShift(std::ifstream &periodStream);

};

#endif
