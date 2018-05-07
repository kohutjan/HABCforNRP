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
  {"seconds", required_argument, 0, 's'},
  {"limit", required_argument, 0, 'l'},
  {"HCR", required_argument, 0, 'h'},
  {"output-frequency", required_argument, 0, 'f'},
  {"output", required_argument, 0, 'o'},
  {"xml-output", required_argument, 0, 'x'},
  {0, 0, 0, 0}};

  string periodFilePath;
  int SN;
  int timeToSolve;
  int limit;
  float HCR;
  int outputFrequency;
  string outputPath;
  string xmlOutputPath;

  cout << endl;
  cout << "Params" << endl;
  cout << "#############################################################" << endl;
  int option_index = 0;
  int opt = 0;
  while ((opt = getopt_long(argc, argv, "p:n:s:l:h:f:o:x:", long_options, &option_index)) != -1)
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

      case 's':
        timeToSolve = stoi(optarg);
        cout << "Time to solve: " << optarg << endl;
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
        cout << "Output frequency in sec: " << optarg << endl;
        break;

      case 'o':
        outputPath = optarg;
        cout << "Output path: " << optarg << endl;
        break;

      case 'x':
        xmlOutputPath = optarg;
        cout << "XML output path: " << optarg << endl;
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
    habc = HABC(SN, timeToSolve, limit, outputFrequency);
  }
  else
  {
    habc = HABC(SN, timeToSolve, limit, HCR, outputFrequency);
  }
  habc.setSchedulingPeriod(schedulingPeriod);
  //habc.TestRosters();
  habc.Run();
  habc.SaveSolution(outputPath);
  habc.SaveSolutionToXML(xmlOutputPath);
  return 0;
}
