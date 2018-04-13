#!/bin/bash

EVALUATOR_PATH=../tests/evaluator.jar
LONGS_FOLDER=../tests/longs
SOLUTION_FOLDER=../tests/runs/$1

python inrc_evaluation.py -j $EVALUATOR_PATH -i "$LONGS_FOLDER/long_xml" -s "$SOLUTION_FOLDER/long/"
python inrc_evaluation.py -j $EVALUATOR_PATH -i "$LONGS_FOLDER/long_hidden_xml" -s "$SOLUTION_FOLDER/long_hidden/"
python inrc_evaluation.py -j $EVALUATOR_PATH -i "$LONGS_FOLDER/long_late_xml" -s "$SOLUTION_FOLDER/long_late/"
python inrc_evaluation.py -j $EVALUATOR_PATH -i "$LONGS_FOLDER/long_hint_xml" -s "$SOLUTION_FOLDER/long_hint/"
