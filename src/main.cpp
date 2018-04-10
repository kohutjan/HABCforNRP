#include <iostream>
#include <string>
#include <getopt.h>

#include "HBAC.hpp"


using namespace std;

int main(int argc, char **argv)
{
  static struct option long_options[] = {
  {"run", required_argument, 0, 'r'},
  {"filters", required_argument, 0, 'f'},
  {0, 0, 0, 0}};

  string periodFilePath;

  cout << endl;
  cout << "Params" << endl;
  cout << "#############################################################" << endl;
  int option_index = 0;
  int opt = 0;
  while ((opt = getopt_long(argc, argv, "p:", long_options, &option_index)) != -1)
  {
    switch (opt)
    {
      case 'p':
        periodFilePath = optarg;
        cout << "Period file path: " << optarg << endl;
        break;

      default:
        break;
    }
  }
  cout << "#############################################################" << endl;
  cout << endl;
  cout << endl;

  if (periodFilePath.empty())
  {
    cout << "Paths to period file have to be set." << endl;
    return -1;
  }

  SchedulingPeriod schedulingPeriod;
  schedulingPeriod.Load(periodFilePath);
  /*
  HBAC hbac;
  hbac.setSchedulingPeriod(schedulingPeriod);
  hbac.InitRosters(1);
  hbac.TestRosters();
  */
  return 0;
}
