#!/bin/bash
mkdir build
cd build

cmake ..
if [ make ]
then
    echo >&2 "Make Failure"
    retval=1
else
    retval = 0

cd ../test
mkdir build
cd build
cmake ..
make

return "$retval"