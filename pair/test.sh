#!/bin/bash
cd ..
WORK_DIR=$(pwd)
cd ./pair

cd "$WORK_DIR"/pair
gcc pair.c test.c 


