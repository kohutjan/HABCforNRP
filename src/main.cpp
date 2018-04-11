#include <iostream>
#include <string>
#include <getopt.h>

#include "HBAC.hpp"


using namespace std;

int main(int argc, char **argv)
{
  static struct option long_options[] = {
  {"period", required_argument, 0, 'p'},
  {"solution-number", required_argument, 0, 'n'},
  {"max-iterations", required_argument, 0, 'm'},
  {"limit", required_argument, 0, 'l'},
  {0, 0, 0, 0}};

  string periodFilePath;
  int SN;
  int MCN;
  int limit;

  cout << endl;
  cout << "Params" << endl;
  cout << "#############################################################" << endl;
  int option_index = 0;
  int opt = 0;
  while ((opt = getopt_long(argc, argv, "p:n:m:l:", long_options, &option_index)) != -1)
  {
    switch (opt)
    {
      case 'p':
        periodFilePath = optarg;
        cout << "Period file path: " << optarg << endl;
        break;

      case 'n':
        SN = stoi(optarg);
        cout << "Number of solutions: " << optarg << endl;
        break;

      case 'm':
        MCN = stoi(optarg);
        cout << "Maximum cycle number: " << optarg << endl;
        break;

      case 'l':
        limit = stoi(optarg);
        cout << "Limit: " << optarg << endl;
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
  HBAC hbac(SN, MCN, limit);
  hbac.setSchedulingPeriod(schedulingPeriod);
  hbac.InitFood();
  hbac.EmployedBees();
  hbac.OnlookerBees();
  return 0;
}
