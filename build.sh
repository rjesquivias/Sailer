#!/bin/bash
mkdir build
cd build

cmake ..
make

cd ../test
mkdir build
cd build
cmake ..
make