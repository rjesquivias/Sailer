#!/bin/bash

git clone https://github.com/google/googletest.git

cd googletest
mkdir build
cd build

cmake .. -DBUILD_GTEST=ON -DBUILD_SHARED_LIBS=ON
make
make install

cd ../../test/build
cmake ..
make