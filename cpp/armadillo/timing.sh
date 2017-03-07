#!/bin/sh

set -v

g++ -larmadillo -O2 -o timing.x timing.cpp
./timing.x
