import sys
import argparse
import os
import subprocess
import shutil
from glob import glob


def parse_args():
    print( ' '.join(sys.argv))

    parser = argparse.ArgumentParser(epilog="Evaluate xml solutions.")

    parser.add_argument('-j', '--inrc-jar',
                        required=True,
                        help="inrc jar evaluator.jar")
    parser.add_argument('-i', '--input-folder',
                        type=str,
                        required=True,
                        help="Folder with xml scheduling periods.")
    parser.add_argument('-s', '--solution-folder',
                        type=str,
                        required=True,
                        help="Folder with xml solutions.")

    args = parser.parse_args()


    return args


def main():
    args = parse_args()

    for runDir in glob(args.solution_folder + "*/"):
        for period in os.listdir(args.input_folder):
            pre, ext = os.path.splitext(period)
            periodPath = os.path.join(args.input_folder, period)
            solutionPath = os.path.join(runDir, pre + "_sol.xml")
            inrcEvalPath = os.path.join(runDir, pre + "_sol.inrc")
            inrcFile = open(inrcEvalPath, 'w')
            inrcArgs = ['java',
                       '-jar', args.inrc_jar,
                       periodPath,
                       solutionPath]
            inrcRun = subprocess.Popen(inrcArgs, stdout=inrcFile)
            inrcRun.wait
            inrcFile.close()

if __name__ == "__main__":
    main()
