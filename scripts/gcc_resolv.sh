#!/bin/bash
GCC=$1

# This script checks the input argument for useable compilers.
# The current Makefile supports clang, but the scripts dont, so
# replace clang with gcc and clang++ with g++
if [ "$GCC" == "clang" ]; then
    GCC=gcc
fi
if [ "$GCC" == "clang++" ]; then
    GCC=g++
fi

echo $GCC

