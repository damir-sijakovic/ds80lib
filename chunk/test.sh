#!/bin/bash
cd ..
WORK_DIR=$(pwd)
cd ./chunk

cd "$WORK_DIR"/chunk
gcc chunk.c test.c 


