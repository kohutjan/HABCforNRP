#!/bin/bash

RUNS_NUMBER=10
EXECUTABLE_PATH=../build/nrp
SOLUTION_NUMBER=10
SECONDS_RUN=453
LIMIT=100
HCR=0.5
MEDIUMS_FOLDER=../tests/mediums
OUTPUT_FOLDER=../tests/runs/$1

rm -r $OUTPUT_FOLDER
mkdir $OUTPUT_FOLDER

python run.py -r $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -s $SECONDS_RUN -l $LIMIT -c $HCR -i "$MEDIUMS_FOLDER/medium_txt" -o "$OUTPUT_FOLDER/medium"
#python run.py -r $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -s $SECONDS_RUN -l $LIMIT -c $HCR -i "$MEDIUMS_FOLDER/medium_hidden_txt" -o "$OUTPUT_FOLDER/medium_hidden"
#python run.py -r $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -s $SECONDS_RUN -l $LIMIT -c $HCR -i "$MEDIUMS_FOLDER/medium_late_txt" -o "$OUTPUT_FOLDER/medium_late"
#python run.py -r $RUNS_NUMBER -e $EXECUTABLE_PATH -n $SOLUTION_NUMBER -s $SECONDS_RUN -l $LIMIT -c $HCR -i "$MEDIUMS_FOLDER/medium_hint_txt" -o "$OUTPUT_FOLDER/medium_hint"
