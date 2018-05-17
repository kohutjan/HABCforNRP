import sys
import argparse
import os
import shutil
from glob import glob
import numpy as np
import re


def parse_args():
    print( ' '.join(sys.argv))

    parser = argparse.ArgumentParser(epilog="Make statistics from solutions.")

    parser.add_argument('-s', '--solution-folder',
                        type=str,
                        required=True,
                        help="Folder with solutions.")
    parser.add_argument('-i', '--inrc',
                        action='store_true',
                        help="If .inrc files are present.")

    args = parser.parse_args()

    return args


def main():
    args = parse_args()

    for instance in glob(args.solution_folder + "*/"):
        statsFileName = os.path.basename(os.path.normpath(instance)) + "_stats.txt"
        statsFilePath = os.path.join(args.solution_folder, statsFileName)
        instanceFile = open(statsFilePath, 'w')
        instanceFile.write('{:^20}'.format("Instance"))
        instanceFile.write('{:^12}'.format("Best"))
        instanceFile.write('{:^12}'.format("Mean"))
        instanceFile.write('{:^12}'.format("Std"))
        if args.inrc:
            instanceFile.write('{:^12}'.format("Inrc mean"))
        instanceFile.write('{:^12}'.format("Random mean"))
        instanceFile.write('\n\n')
        runDirs = glob(instance + "*/")
        meanOfMeans = []
        for solutionFileName in NaturalSort(os.listdir(runDirs[0])):
            if solutionFileName.endswith(".txt"):
                solutionRandomPenalty = np.empty(len(runDirs))
                solutionPenalty = np.empty(len(runDirs))
                if args.inrc:
                    inrcSolutionPenalty = np.empty(len(runDirs))
                for i, runDir in enumerate(runDirs):
                    solutionPath = os.path.join(runDir, solutionFileName)
                    with open(solutionPath) as f:
                        txtSolutionLines = f.read().splitlines()
                    if args.inrc:
                        pre, ext = os.path.splitext(solutionPath)
                        inrcSolutionPath = pre + ".inrc"
                        with open(inrcSolutionPath) as f:
                            txtInrcSolutionLines = f.read().splitlines()
                    solutionPenalty[i] = int(txtSolutionLines[-3].split()[-1])
                    solutionRandomPenalty[i] = int(txtSolutionLines[-2].split()[-1])
                    if args.inrc:
                        inrcSolutionPenalty[i] = int(txtInrcSolutionLines[-2].split()[-1])
                instanceFile.write('{:^20}'.format(solutionFileName.split("_sol")[0]))
                instanceFile.write('{:^12}'.format(np.amin(solutionPenalty)))
                instanceFile.write('{:^12}'.format(solutionPenalty.mean()))
                instanceFile.write('{:^12}'.format(np.std(solutionPenalty)))
                meanOfMeans.append(solutionPenalty.mean())
                if args.inrc:
                    instanceFile.write('{:^12}'.format(inrcSolutionPenalty.mean()))
                instanceFile.write('{:^12}'.format(solutionRandomPenalty.mean()))
                instanceFile.write('\n')
        instanceFile.write("\nMean of means: {}".format(np.asarray(meanOfMeans).mean()))
        instanceFile.close()

#https://stackoverflow.com/questions/2669059/how-to-sort-alpha-numeric-set-in-python
def NaturalSort(l):
    """ Sort the given iterable in the way that humans expect."""
    convert = lambda text: int(text) if text.isdigit() else text
    alphanum_key = lambda key: [ convert(c) for c in re.split('([0-9]+)', key) ]
    return sorted(l, key = alphanum_key)

if __name__ == "__main__":
    main()
