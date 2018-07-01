#!/bin/sh

set -v

g++ -larmadillo -o arma_test_save.x arma_test_save.cpp
./arma_test_save.x
