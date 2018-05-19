#!/bin/bash

RUNS_NUMBER=1
EXECUTABLE_PATH=../build/nrp
SOLUTION_NUMBER=10
ROSTER_ITER_SECONDS=4000000
LIMIT=100
SPRINTS_FOLDER=../tests/sprints
OUTPUT_FOLDER0=../tests/runs/$1_case0
OUTPUT_FOLDER1=../tests/runs/$1_case1
OUTPUT_FOLDER2=../tests/runs/$1_case2
OUTPUT_FOLDER3=../tests/runs/$1_case3
MODE='-r'

python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0 -p "$SPRINTS_FOLDER/sprint_late_txt" -o "$OUTPUT_FOLDER0/sprint_late" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0 -p "$SPRINTS_FOLDER/sprint_hint_txt" -o "$OUTPUT_FOLDER0/sprint_hint" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0 -p "$SPRINTS_FOLDER/sprint_hidden_txt" -o "$OUTPUT_FOLDER0/sprint_hidden" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0 -p "$SPRINTS_FOLDER/sprint_txt" -o "$OUTPUT_FOLDER0/sprint" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0.1 -p "$SPRINTS_FOLDER/sprint_late_txt" -o "$OUTPUT_FOLDER1/sprint_late" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0.1 -p "$SPRINTS_FOLDER/sprint_hint_txt" -o "$OUTPUT_FOLDER1/sprint_hint" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0.1 -p "$SPRINTS_FOLDER/sprint_hidden_txt" -o "$OUTPUT_FOLDER1/sprint_hidden" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0.1 -p "$SPRINTS_FOLDER/sprint_txt" -o "$OUTPUT_FOLDER1/sprint" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0.3 -p "$SPRINTS_FOLDER/sprint_late_txt" -o "$OUTPUT_FOLDER2/sprint_late" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0.3 -p "$SPRINTS_FOLDER/sprint_hint_txt" -o "$OUTPUT_FOLDER2/sprint_hint" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0.3 -p "$SPRINTS_FOLDER/sprint_hidden_txt" -o "$OUTPUT_FOLDER2/sprint_hidden" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0.3 -p "$SPRINTS_FOLDER/sprint_txt" -o "$OUTPUT_FOLDER2/sprint" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0.5 -p "$SPRINTS_FOLDER/sprint_late_txt" -o "$OUTPUT_FOLDER3/sprint_late" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0.5 -p "$SPRINTS_FOLDER/sprint_hint_txt" -o "$OUTPUT_FOLDER3/sprint_hint" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0.5 -p "$SPRINTS_FOLDER/sprint_hidden_txt" -o "$OUTPUT_FOLDER3/sprint_hidden" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0.5 -p "$SPRINTS_FOLDER/sprint_txt" -o "$OUTPUT_FOLDER3/sprint" $MODE
