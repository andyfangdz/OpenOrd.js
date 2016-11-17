#!/bin/bash

rm -rf dist bin
mkdir bin

emcc src/DensityGrid.cpp src/graph.cpp -std=c++11 -Wall -o bin/OpenOrd.js -O3 --bind -s TOTAL_MEMORY=1073741824

cp -a bin/. dist
cp -a bin/. docs
