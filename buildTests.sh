#!/bin/bash
cd test
mkdir build
cd build

cmake .. || exit 1
make || exit 1