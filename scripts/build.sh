#!/bin/bash

echo "Building project..."
mkdir build
cd build
cmake ..
cmake --build .