import sys
import argparse
import os
import subprocess
import shutil


def parse_args():
    print( ' '.join(sys.argv))

    parser = argparse.ArgumentParser(epilog="Run for NRP")

    parser.add_argument('-e', '--nrp-executable',
                        required=True,
                        help="nrp exacutable")
    parser.add_argument('-n', '--solution-number',
                        type=int,
                        required=True,
                        help="Number of rosters.")
    parser.add_argument('-i', '--iter-seconds',
                        type=int,
                        required=True,
                        help="Time / iterations to solve.")
    parser.add_argument('-l', '--limit',
                        type=int,
                        required=True,
                        help="Limit.")
    parser.add_argument('-c', '--HCR',
                        type=float,
                        default=0.0,
                        help="Hill climbing constant.")
    parser.add_argument('-rn', '--run-number',
                        type=int,
                        required=True,
                        help="Number of runs.")
    parser.add_argument('-p', '--periods-folder',
                        type=str,
                        required=True,
                        help="Folder with scheduling periods.")
    parser.add_argument('-o', '--output-folder',
                        type=str,
                        required=True,
                        help="Folder to store output files.")
    parser.add_argument('-t', '--time-mode',
                        action='store_true',
                        help="Use time in sec.")
    parser.add_argument('-v', '--iter-mode',
                        action='store_true',
                        help="Use iterations.")
    parser.add_argument('-r', '--roster-mode',
                        action='store_true',
                        help="Use rosters limit.")
    parser.add_argument('-s', '--verbose',
                        action='store_true',
                        help="Print output of nrp to stdout.")

    args = parser.parse_args()


    return args


def main():
    args = parse_args()

    if args.verbose:
        stdOut = sys.stdout
    else:
        stdOut = open(os.devnull, 'w')

    if os.path.exists(args.output_folder):
        shutil.rmtree(args.output_folder)
        os.makedirs(args.output_folder)
    else:
        os.makedirs(args.output_folder)

    for i in range(args.run_number):
        outputFolder = os.path.join(args.output_folder, str(i))
        os.makedirs(outputFolder)
        for period in os.listdir(args.periods_folder):
            pre, ext = os.path.splitext(period)
            periodPath = os.path.join(args.periods_folder, period)
            outputPath = os.path.join(outputFolder, pre + "_sol.txt")
            xmlOutputPath = os.path.join(outputFolder, pre + "_sol.xml")
            nrpArgs = [args.nrp_executable,
                       '-p', periodPath,
                       '-n', str(args.solution_number),
                       '-i', str(args.iter_seconds),
                       '-l', str(args.limit),
                       '-h', str(args.HCR),
                       '-f', str(args.iter_seconds),
                       '-o', outputPath,
                       '-x', xmlOutputPath]
            if args.time_mode:
                nrpArgs.append('-t')
            if args.iter_mode:
                nrpArgs.append('-v')
            if args.roster_mode:
                nrpArgs.append('-r')
            nrpRun = subprocess.Popen(nrpArgs, stdout=stdOut)
            nrpRun.wait()

if __name__ == "__main__":
    main()
