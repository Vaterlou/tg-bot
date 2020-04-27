#!/usr/bin/env bash
CPU_CORES=$(getconf _NPROCESSORS_ONLN)
mkdir -p build
cd build
cmake -DBUILD_TESTS=true .. 
make -j $CPU_CORES