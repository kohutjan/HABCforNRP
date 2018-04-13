#!/bin/bash

RUNS_NUMBER=2
EXECUTABLE_PATH=../build/nrp
SOLUTION_NUMBER=10
SECONDS_RUN=1
LIMIT=100
LONGS_FOLDER=../tests/longs
OUTPUT_FOLDER=../tests/runs/$1

rm -r $OUTPUT_FOLDER
mkdir $OUTPUT_FOLDER

python run.py -r $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -s $SECONDS_RUN -l $LIMIT -i "$LONGS_FOLDER/long_txt" -o "$OUTPUT_FOLDER/long"
python run.py -r $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -s $SECONDS_RUN -l $LIMIT -i "$LONGS_FOLDER/long_hidden_txt" -o "$OUTPUT_FOLDER/long_hidden"
python run.py -r $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -s $SECONDS_RUN -l $LIMIT -i "$LONGS_FOLDER/long_late_txt" -o "$OUTPUT_FOLDER/long_late"
python run.py -r $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -s $SECONDS_RUN -l $LIMIT -i "$LONGS_FOLDER/long_hint_txt" -o "$OUTPUT_FOLDER/long_hint"
