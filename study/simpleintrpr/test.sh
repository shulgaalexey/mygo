#! /bin/bash

echo Building tests...
cd ./test/src
rm *.o *.out
make

echo Testing...
./test_all.out

cd ../..
