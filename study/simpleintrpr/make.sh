#! /bin/bash

echo Building....
cd ./src
make
cd ..

echo Building tests...
cd ./test/src
make

echo Testing...
./test_all.out

cd ../..
