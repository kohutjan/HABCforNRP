#!/bin/bash

EVALUATOR_PATH=../tests/evaluator.jar
MEDIUMS_FOLDER=../tests/mediums
SOLUTION_FOLDER=../tests/runs/$1

python inrc_evaluation.py -j $EVALUATOR_PATH -i "$MEDIUMS_FOLDER/medium_xml" -s "$SOLUTION_FOLDER/medium/"
python inrc_evaluation.py -j $EVALUATOR_PATH -i "$MEDIUMS_FOLDER/medium_hidden_xml" -s "$SOLUTION_FOLDER/medium_hidden/"
python inrc_evaluation.py -j $EVALUATOR_PATH -i "$MEDIUMS_FOLDER/medium_late_xml" -s "$SOLUTION_FOLDER/medium_late/"
python inrc_evaluation.py -j $EVALUATOR_PATH -i "$MEDIUMS_FOLDER/medium_hint_xml" -s "$SOLUTION_FOLDER/medium_hint/"
