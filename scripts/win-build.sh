#!/bin/bash

# sudo apt install mingw-w64
# sudo apt install ninja-build

echo "Building game for Windows..."

rm -rf build-windows
mkdir -p build-windows
cd build-windows
cmake .. -DCMAKE_TOOLCHAIN_FILE=../toolchain-mingw.cmake -G "Ninja"
ninja
