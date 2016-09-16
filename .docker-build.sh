#!/bin/bash

mkdir build
cd build
cmake ..
# Second CMake run is not accidental; build fails otherwise. 
# Probably because of the custom toolchain or custom CMAKE_C_LINK_EXECUTABLE
cmake ..
make -j$(nproc)

cp api-scan /usr/local/bin/