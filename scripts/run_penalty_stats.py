import sys
import argparse
import os
from glob import glob
import numpy as np
import re
import penalty_stats

def parse_args():
    print( ' '.join(sys.argv))

    parser = argparse.ArgumentParser(epilog="Make penalty statistics from solutions.")

    parser.add_argument('-s', '--solution-folder',
                        type=str,
                        required=True,
                        help="Folder with solutions.")

    args = parser.parse_args()

    return args


def main():
    args = parse_args()
    solutionPaths = []
    penaltyFilePath = os.path.join(args.solution_folder, "penalty_stats.txt")
    for instance in glob(args.solution_folder + "*/"):
        runDirs = glob(instance + "*/")
        for solutionFileName in NaturalSort(os.listdir(runDirs[0])):
            if solutionFileName.endswith(".txt"):
                for i, runDir in enumerate(runDirs):
                    solutionPath = os.path.join(runDir, solutionFileName)
                    solutionPaths.append(solutionPath)


    penalties = penalty_stats.GetMeanPenalties(solutionPaths)
    penaltyFile = open(os.path.join(args.solution_folder, "penalty_stats.txt"), 'w')
    penaltyFile.write("numAssigmentsMean: {}\n".format(penalties[0]))
    penaltyFile.write("consecutiveWorkingDaysMean: {}\n".format(penalties[1]))
    penaltyFile.write("consecutiveFreeDaysMean: {}\n".format(penalties[2]))
    penaltyFile.write("consecutiveWorkingWeekendsMean: {}\n".format(penalties[3]))
    penaltyFile.write("maxWorkingWeekendsInFourWeeksMean: {}\n".format(penalties[4]))
    penaltyFile.write("completeWeekendsMean: {}\n".format(penalties[5]))
    penaltyFile.write("identShiftTypesDuringWeekendMean: {}\n".format(penalties[6]))
    penaltyFile.write("noNightShiftBeforeFreeWeekendMean: {}\n".format(penalties[7]))
    penaltyFile.write("twoFreeDaysAfterNightShiftsMean: {}\n".format(penalties[8]))
    penaltyFile.write("requestedDaysMean: {}\n".format(penalties[9]))
    penaltyFile.write("requstedShiftsMean: {}\n".format(penalties[10]))
    penaltyFile.write("alternativeSkillCategoryMean: {}\n".format(penalties[11]))
    penaltyFile.write("unwantedPatternsMean: {}\n".format(penalties[12]))
    penaltyFile.close()

#https://stackoverflow.com/questions/2669059/how-to-sort-alpha-numeric-set-in-python
def NaturalSort(l):
    """ Sort the given iterable in the way that humans expect."""
    convert = lambda text: int(text) if text.isdigit() else text
    alphanum_key = lambda key: [ convert(c) for c in re.split('([0-9]+)', key) ]
    return sorted(l, key = alphanum_key)

if __name__ == "__main__":
    main()
