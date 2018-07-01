#!/bin/sh

set -v

g++ -larmadillo -o arma_test_zero.x arma_test_zero.cpp
./arma_test_zero.x
