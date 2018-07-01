#!/bin/bash

name=tensor_declaration

set -v

rm ./${name}.x

# g++ -o ${name}.x ${name}.cpp
g++ -I/usr/include/eigen3 -I/usr/include/eigen3/unsupported -std=c++11 -o ${name}.x ${name}.cpp

./${name}.x
