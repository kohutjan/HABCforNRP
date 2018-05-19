#include <iostream>
#include <string>
#include <getopt.h>

#include "HABC.hpp"


using namespace std;

int main(int argc, char **argv)
{
  static struct option long_options[] = {
  {"period", required_argument, 0, 'p'},
  {"solution-number", required_argument, 0, 'n'},
  {"rosters-iter-seconds", required_argument, 0, 'i'},
  {"limit", required_argument, 0, 'l'},
  {"HCR", required_argument, 0, 'h'},
  {"output-frequency", required_argument, 0, 'f'},
  {"output", required_argument, 0, 'o'},
  {"xml-output", required_argument, 0, 'x'},
  {"time-mode", no_argument, 0, 't'},
  {"roster-mode", no_argument, 0, 'r'},
  {"iter-mode", no_argument, 0, 'v'},
  {0, 0, 0, 0}};

  string periodFilePath;
  int SN;
  int timeIterRosterToSolve;
  int limit;
  float HCR;
  int outputFrequency;
  string outputPath;
  string xmlOutputPath;
  bool timeMode = false;
  bool iterMode = false;
  bool rosterMode = false;

  cout << endl;
  cout << "Params" << endl;
  cout << "#############################################################" << endl;
  int option_index = 0;
  int opt = 0;
  while ((opt = getopt_long(argc, argv, "p:n:i:l:h:f:o:x:trv", long_options, &option_index)) != -1)
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

      case 'i':
        timeIterRosterToSolve = stoi(optarg);
        cout << "Time to solve / iterations / rosters limit: " << optarg << endl;
        break;

      case 'l':
        limit = stoi(optarg);
        cout << "Limit: " << optarg << endl;
        break;

      case 'h':
        HCR = stof(optarg);
        cout << "Hill climbing constant: " << optarg << endl;
        break;

      case 'f':
        outputFrequency = stoi(optarg);
        cout << "Output frequency in sec / iterations: " << optarg << endl;
        break;

      case 'o':
        outputPath = optarg;
        cout << "Output path: " << optarg << endl;
        break;

      case 'x':
        xmlOutputPath = optarg;
        cout << "XML output path: " << optarg << endl;
        break;

      case 't':
        timeMode = true;
        cout << "Time mode set to True" << endl;
        break;

      case 'r':
        rosterMode = true;
        cout << "Roster limit mode set to True" << endl;
        break;

      case 'v':
        iterMode = true;
        cout << "Iterations mode set to True" << endl;
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
  HABC habc;
  if (HCR == 0.0)
  {
    if (timeMode)
    {
      habc = HABC(SN, timeIterRosterToSolve, limit, outputFrequency, true);
    }
    else
    {
      habc = HABC(SN, limit, true);
    }
  }
  else
  {
    if (timeMode)
    {
      habc = HABC(SN, timeIterRosterToSolve, limit, HCR, outputFrequency, false);
    }
    else
    {
      habc = HABC(SN, limit, HCR, false);
    }
  }
  habc.setSchedulingPeriod(schedulingPeriod);
  if (timeMode)
  {
    habc.Run();
  }
  else {
  if (iterMode)
  {
    habc.RunIter(timeIterRosterToSolve, outputFrequency);
  }
  else {
  if (rosterMode)
  {
    habc.RunRostersLimit(timeIterRosterToSolve, outputFrequency);
  }}}
  if (not outputPath.empty())
  {
    habc.SaveSolution(outputPath);
  }
  if (not xmlOutputPath.empty())
  {
    habc.SaveSolutionToXML(xmlOutputPath);
  }
  return 0;
}
