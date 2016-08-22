#!/bin/bash

rm -rf dist build
rm docs/OpenOrd.js docs/OpenOrd.js.mem

mkdir build
mkdir dist

cd build

emcmake cmake ..
make

cp -a bin/. ../dist 
cp -a bin/. ../docs 
