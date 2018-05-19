#!/bin/bash

RUNS_NUMBER=5
EXECUTABLE_PATH=../build/nrp
SOLUTION_NUMBER=10
SPRINTS_FOLDER=../tests/sprints
OUTPUT_FOLDER=../tests/runs/graphs_params_stats_roster_prob
MODE='-r'

#python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i 20000 -l 100 -c 0 -p "$SPRINTS_FOLDER/sprint_txt" -o "$OUTPUT_FOLDER/sprint_20000_100/sprint" $MODE
#python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i 20000 -l 100 -c 0.1 -p "$SPRINTS_FOLDER/sprint_txt" -o "$OUTPUT_FOLDER/sprint_20000_100_01/sprint" $MODE
#python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i 20000 -l 100 -c 0.3 -p "$SPRINTS_FOLDER/sprint_txt" -o "$OUTPUT_FOLDER/sprint_20000_100_03/sprint" $MODE
#python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i 20000 -l 100 -c 0.5 -p "$SPRINTS_FOLDER/sprint_txt" -o "$OUTPUT_FOLDER/sprint_20000_100_05/sprint" $MODE
#python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i 20000 -l 500 -c 0 -p "$SPRINTS_FOLDER/sprint_txt" -o "$OUTPUT_FOLDER/sprint_20000_500/sprint" $MODE
#python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i 20000 -l 500 -c 0.1 -p "$SPRINTS_FOLDER/sprint_txt" -o "$OUTPUT_FOLDER/sprint_20000_500_01/sprint" $MODE
#python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i 20000 -l 500 -c 0.3 -p "$SPRINTS_FOLDER/sprint_txt" -o "$OUTPUT_FOLDER/sprint_20000_500_03/sprint" $MODE
#python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i 20000 -l 500 -c 0.5 -p "$SPRINTS_FOLDER/sprint_txt" -o "$OUTPUT_FOLDER/sprint_20000_500_05/sprint" $MODE
#python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i 20000 -l 1000 -c 0 -p "$SPRINTS_FOLDER/sprint_txt" -o "$OUTPUT_FOLDER/sprint_20000_1000/sprint" $MODE
#python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i 20000 -l 1000 -c 0.1 -p "$SPRINTS_FOLDER/sprint_txt" -o "$OUTPUT_FOLDER/sprint_20000_1000_01/sprint" $MODE
#python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i 20000 -l 1000 -c 0.3 -p "$SPRINTS_FOLDER/sprint_txt" -o "$OUTPUT_FOLDER/sprint_20000_1000_03/sprint" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i 20000 -l 1000 -c 0.5 -p "$SPRINTS_FOLDER/sprint_hint_txt" -o "$OUTPUT_FOLDER/sprint_20000_1000_05_4/sprint_hint" $MODE
#python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n 20 -i 20000 -l 1000 -c 0.5 -p "$SPRINTS_FOLDER/sprint_txt" -o "$OUTPUT_FOLDER/sprint_20000_1000_05_20/sprint" $MODE
#python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n 40 -i 20000 -l 1000 -c 0.5 -p "$SPRINTS_FOLDER/sprint_txt" -o "$OUTPUT_FOLDER/sprint_20000_1000_05_40/sprint" $MODE
#python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i 40000 -l 100 -c 0.5 -p "$SPRINTS_FOLDER/sprint_txt" -o "$OUTPUT_FOLDER/sprint_40000_100_05/sprint" $MODE
#python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i 40000 -l 500 -c 0.5 -p "$SPRINTS_FOLDER/sprint_txt" -o "$OUTPUT_FOLDER/sprint_40000_500_05/sprint" $MODE
#python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i 40000 -l 1000 -c 0 -p "$SPRINTS_FOLDER/sprint_txt" -o "$OUTPUT_FOLDER/sprint_40000_1000/sprint" $MODE
#python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i 40000 -l 1000 -c 0.1 -p "$SPRINTS_FOLDER/sprint_txt" -o "$OUTPUT_FOLDER/sprint_40000_1000_01/sprint" $MODE
#python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i 40000 -l 1000 -c 0.3 -p "$SPRINTS_FOLDER/sprint_txt" -o "$OUTPUT_FOLDER/sprint_40000_1000_03/sprint" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i 40000 -l 1000 -c 0.5 -p "$SPRINTS_FOLDER/sprint_hint_txt" -o "$OUTPUT_FOLDER/sprint_40000_1000_05_4/sprint_hint" $MODE
#python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n 20 -i 40000 -l 1000 -c 0.5 -p "$SPRINTS_FOLDER/sprint_txt" -o "$OUTPUT_FOLDER/sprint_40000_1000_05_20/sprint" $MODE
#python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n 40 -i 40000 -l 1000 -c 0.5 -p "$SPRINTS_FOLDER/sprint_txt" -o "$OUTPUT_FOLDER/sprint_40000_1000_05_40/sprint" $MODE
#python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i 60000 -l 100 -c 0.5 -p "$SPRINTS_FOLDER/sprint_txt" -o "$OUTPUT_FOLDER/sprint_60000_100_05/sprint" $MODE
#python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i 60000 -l 500 -c 0.5 -p "$SPRINTS_FOLDER/sprint_txt" -o "$OUTPUT_FOLDER/sprint_60000_500_05/sprint" $MODE
#python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n 20 -i 60000 -l 1000 -c 0.5 -p "$SPRINTS_FOLDER/sprint_txt" -o "$OUTPUT_FOLDER/sprint_60000_1000_05_20/sprint" $MODE
#python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n 40 -i 60000 -l 1000 -c 0.5 -p "$SPRINTS_FOLDER/sprint_txt" -o "$OUTPUT_FOLDER/sprint_60000_1000_05_40/sprint" $MODE
#python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i 60000 -l 1000 -c 0 -p "$SPRINTS_FOLDER/sprint_txt" -o "$OUTPUT_FOLDER/sprint_60000_1000/sprint" $MODE
#python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i 60000 -l 1000 -c 0.1 -p "$SPRINTS_FOLDER/sprint_txt" -o "$OUTPUT_FOLDER/sprint_60000_1000_01/sprint" $MODE
#python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i 60000 -l 1000 -c 0.3 -p "$SPRINTS_FOLDER/sprint_txt" -o "$OUTPUT_FOLDER/sprint_60000_1000_03/sprint" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i 60000 -l 1000 -c 0.5 -p "$SPRINTS_FOLDER/sprint_hint_txt" -o "$OUTPUT_FOLDER/sprint_60000_1000_05_4/sprint_hint" $MODE
