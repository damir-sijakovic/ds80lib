#!/bin/bash
cd ..
WORK_DIR=$(pwd)
cd ./vector

cd "$WORK_DIR"/vector
gcc vector.c test.c 


