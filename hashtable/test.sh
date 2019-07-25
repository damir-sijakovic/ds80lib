#!/bin/bash
cd ..
WORK_DIR=$(pwd)
cd ./hashtable

##### pair module
cd "$WORK_DIR"/pair
./mkobj.sh
mv pair.o "$WORK_DIR"/hashtable

##### vector module
cd "$WORK_DIR"/vector
./mkobj.sh
mv vector.o "$WORK_DIR"/hashtable

##### linkedlist module
cd "$WORK_DIR"/linkedlist
./mkobj.sh
mv linkedlist.o "$WORK_DIR"/hashtable

cd "$WORK_DIR"/hashtable
gcc pair.o vector.o linkedlist.o hashtable.c test.c 

rm pair.o vector.o linkedlist.o


