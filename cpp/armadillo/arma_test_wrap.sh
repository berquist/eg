#!/bin/sh

CXX=icpc

set -v

rm ./arma_test_wrap.x

# ${CXX} -mavx -larmadillo -o arma_test_wrap.x arma_test_wrap.cpp
g++ -larmadillo -o arma_test_wrap.x arma_test_wrap.cpp

./arma_test_wrap.x
