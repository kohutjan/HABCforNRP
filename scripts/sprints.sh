#!/bin/bash

RUNS_NUMBER=10
EXECUTABLE_PATH=../build/nrp
SOLUTION_NUMBER=10
SECONDS_RUN=7
LIMIT=100
HCR=0.7
SPRINTS_FOLDER=../tests/sprints
OUTPUT_FOLDER=../tests/runs/$1

rm -r $OUTPUT_FOLDER
mkdir $OUTPUT_FOLDER

python run.py -r $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -s $SECONDS_RUN -l $LIMIT -c $HCR -i "$SPRINTS_FOLDER/sprint_txt" -o "$OUTPUT_FOLDER/sprint"
python run.py -r $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -s $SECONDS_RUN -l $LIMIT -c $HCR -i "$SPRINTS_FOLDER/sprint_hidden_txt" -o "$OUTPUT_FOLDER/sprint_hidden"
python run.py -r $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -s $SECONDS_RUN -l $LIMIT -c $HCR -i "$SPRINTS_FOLDER/sprint_late_txt" -o "$OUTPUT_FOLDER/sprint_late"
python run.py -r $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -s $SECONDS_RUN -l $LIMIT -c $HCR -i "$SPRINTS_FOLDER/sprint_hint_txt" -o "$OUTPUT_FOLDER/sprint_hint"
