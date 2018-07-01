#!/bin/sh

set -v

g++ -larmadillo -o arma_test_mask_index.x arma_test_mask_index.cpp
./arma_test_mask_index.x
