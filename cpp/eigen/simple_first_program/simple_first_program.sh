#!/bin/bash

name=simple_first_program

set -v

rm ./${name}.x

# g++ -o ${name}.x ${name}.cpp
g++ -I/usr/include/eigen3 -std=c++14 -o ${name}.x ${name}.cpp

./${name}.x
