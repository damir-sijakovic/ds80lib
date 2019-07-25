#!/bin/bash
cd ..
WORK_DIR=$(pwd)
cd ./linkedlist

##### vector module
cd "$WORK_DIR"/vector
./mkobj.sh
mv vector.o "$WORK_DIR"/linkedlist

cd "$WORK_DIR"/linkedlist
gcc vector.o linkedlist.c test.c 

rm vector.o

