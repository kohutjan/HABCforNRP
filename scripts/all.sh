#!/bin/bash

RUNS_NUMBER=5
EXECUTABLE_PATH=../build/nrp
SOLUTION_NUMBER=10
ROSTER_ITER_SECONDS=20000
LIMIT=1000
TEST_FOLDER=../tests
OUTPUT_FOLDER0=../tests/runs/$1_case0
OUTPUT_FOLDER1=../tests/runs/$1_case1
OUTPUT_FOLDER2=../tests/runs/$1_case2
OUTPUT_FOLDER3=../tests/runs/$1_case3
MODE='-r'

python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0 -p "$TEST_FOLDER/sprints/sprint_txt" -o "$OUTPUT_FOLDER0/sprint" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0 -p "$TEST_FOLDER/sprints/sprint_hidden_txt" -o "$OUTPUT_FOLDER0/sprint_hidden" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0 -p "$TEST_FOLDER/sprints/sprint_late_txt" -o "$OUTPUT_FOLDER0/sprint_late" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0 -p "$TEST_FOLDER/sprints/sprint_hint_txt" -o "$OUTPUT_FOLDER0/sprint_hint" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0.1 -p "$TEST_FOLDER/sprints/sprint_txt" -o "$OUTPUT_FOLDER1/sprint" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0.1 -p "$TEST_FOLDER/sprints/sprint_hidden_txt" -o "$OUTPUT_FOLDER1/sprint_hidden" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0.1 -p "$TEST_FOLDER/sprints/sprint_late_txt" -o "$OUTPUT_FOLDER1/sprint_late" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0.1 -p "$TEST_FOLDER/sprints/sprint_hint_txt" -o "$OUTPUT_FOLDER1/sprint_hint" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0.3 -p "$TEST_FOLDER/sprints/sprint_txt" -o "$OUTPUT_FOLDER2/sprint" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0.3 -p "$TEST_FOLDER/sprints/sprint_hidden_txt" -o "$OUTPUT_FOLDER2/sprint_hidden" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0.3 -p "$TEST_FOLDER/sprints/sprint_late_txt" -o "$OUTPUT_FOLDER2/sprint_late" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0.3 -p "$TEST_FOLDER/sprints/sprint_hint_txt" -o "$OUTPUT_FOLDER2/sprint_hint" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0.5 -p "$TEST_FOLDER/sprints/sprint_txt" -o "$OUTPUT_FOLDER3/sprint" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0.5 -p "$TEST_FOLDER/sprints/sprint_hidden_txt" -o "$OUTPUT_FOLDER3/sprint_hidden" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0.5 -p "$TEST_FOLDER/sprints/sprint_late_txt" -o "$OUTPUT_FOLDER3/sprint_late" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0.5 -p "$TEST_FOLDER/sprints/sprint_hint_txt" -o "$OUTPUT_FOLDER3/sprint_hint" $MODE

python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0 -p "$TEST_FOLDER/mediums/medium_txt" -o "$OUTPUT_FOLDER0/medium" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0 -p "$TEST_FOLDER/mediums/medium_hidden_txt" -o "$OUTPUT_FOLDER0/medium_hidden" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0 -p "$TEST_FOLDER/mediums/medium_late_txt" -o "$OUTPUT_FOLDER0/medium_late" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0 -p "$TEST_FOLDER/mediums/medium_hint_txt" -o "$OUTPUT_FOLDER0/medium_hint" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0.1 -p "$TEST_FOLDER/mediums/medium_txt" -o "$OUTPUT_FOLDER1/medium" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0.1 -p "$TEST_FOLDER/mediums/medium_hidden_txt" -o "$OUTPUT_FOLDER1/medium_hidden" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0.1 -p "$TEST_FOLDER/mediums/medium_late_txt" -o "$OUTPUT_FOLDER1/medium_late" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0.1 -p "$TEST_FOLDER/mediums/medium_hint_txt" -o "$OUTPUT_FOLDER1/medium_hint" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0.3 -p "$TEST_FOLDER/mediums/medium_txt" -o "$OUTPUT_FOLDER2/medium" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0.3 -p "$TEST_FOLDER/mediums/medium_hidden_txt" -o "$OUTPUT_FOLDER2/medium_hidden" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0.3 -p "$TEST_FOLDER/mediums/medium_late_txt" -o "$OUTPUT_FOLDER2/medium_late" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0.3 -p "$TEST_FOLDER/mediums/medium_hint_txt" -o "$OUTPUT_FOLDER2/medium_hint" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0.5 -p "$TEST_FOLDER/mediums/medium_txt" -o "$OUTPUT_FOLDER3/medium" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0.5 -p "$TEST_FOLDER/mediums/medium_hidden_txt" -o "$OUTPUT_FOLDER3/medium_hidden" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0.5 -p "$TEST_FOLDER/mediums/medium_late_txt" -o "$OUTPUT_FOLDER3/medium_late" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0.5 -p "$TEST_FOLDER/mediums/medium_hint_txt" -o "$OUTPUT_FOLDER3/medium_hint" $MODE

python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0 -p "$TEST_FOLDER/longs/long_txt" -o "$OUTPUT_FOLDER0/long" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0 -p "$TEST_FOLDER/longs/long_hidden_txt" -o "$OUTPUT_FOLDER0/long_hidden" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0 -p "$TEST_FOLDER/longs/long_late_txt" -o "$OUTPUT_FOLDER0/long_late" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0 -p "$TEST_FOLDER/longs/long_hint_txt" -o "$OUTPUT_FOLDER0/long_hint" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0.1 -p "$TEST_FOLDER/longs/long_txt" -o "$OUTPUT_FOLDER1/long" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0.1 -p "$TEST_FOLDER/longs/long_hidden_txt" -o "$OUTPUT_FOLDER1/long_hidden" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0.1 -p "$TEST_FOLDER/longs/long_late_txt" -o "$OUTPUT_FOLDER1/long_late" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0.1 -p "$TEST_FOLDER/longs/long_hint_txt" -o "$OUTPUT_FOLDER1/long_hint" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0.3 -p "$TEST_FOLDER/longs/long_txt" -o "$OUTPUT_FOLDER2/long" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0.3 -p "$TEST_FOLDER/longs/long_hidden_txt" -o "$OUTPUT_FOLDER2/long_hidden" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0.3 -p "$TEST_FOLDER/longs/long_late_txt" -o "$OUTPUT_FOLDER2/long_late" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0.3 -p "$TEST_FOLDER/longs/long_hint_txt" -o "$OUTPUT_FOLDER2/long_hint" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0.5 -p "$TEST_FOLDER/longs/long_txt" -o "$OUTPUT_FOLDER3/long" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0.5 -p "$TEST_FOLDER/longs/long_hidden_txt" -o "$OUTPUT_FOLDER3/long_hidden" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0.5 -p "$TEST_FOLDER/longs/long_late_txt" -o "$OUTPUT_FOLDER3/long_late" $MODE
python run.py -rn $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -i $ROSTER_ITER_SECONDS -l $LIMIT -c 0.5 -p "$TEST_FOLDER/longs/long_hint_txt" -o "$OUTPUT_FOLDER3/long_hint" $MODE
