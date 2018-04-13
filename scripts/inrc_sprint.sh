#!/bin/bash

EVALUATOR_PATH=../tests/evaluator.jar
SPRINTS_FOLDER=../tests/sprints
SOLUTION_FOLDER=../tests/runs/$1

python inrc_evaluation.py -j $EVALUATOR_PATH -i "$SPRINTS_FOLDER/sprint_xml" -s "$SOLUTION_FOLDER/sprint/"
python inrc_evaluation.py -j $EVALUATOR_PATH -i "$SPRINTS_FOLDER/sprint_hidden_xml" -s "$SOLUTION_FOLDER/sprint_hidden/"
python inrc_evaluation.py -j $EVALUATOR_PATH -i "$SPRINTS_FOLDER/sprint_late_xml" -s "$SOLUTION_FOLDER/sprint_late/"
python inrc_evaluation.py -j $EVALUATOR_PATH -i "$SPRINTS_FOLDER/sprint_hint_xml" -s "$SOLUTION_FOLDER/sprint_hint/"
