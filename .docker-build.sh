#!/bin/bash

mkdir build
cd build

export CCACHE_DIR=/var/ccache
export CCACHE_CPP2=true

cmake ..
# Second CMake run is not accidental; build fails otherwise. 
# Probably because of the custom toolchain or custom CMAKE_C_LINK_EXECUTABLE
cmake ..
make -j$(nproc)

cp api-scan /usr/local/bin/