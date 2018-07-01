#!/bin/sh

CXX=icpc

set -v

rm ./inv_sqrt.x

# ${CXX} -mavx -larmadillo -o inv_sqrt.x inv_sqrt.cpp
g++ -larmadillo -o inv_sqrt.x inv_sqrt.cpp

./inv_sqrt.x
