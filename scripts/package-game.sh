#!/bin/bash

echo "Packaging game for Windows..."

mkdir -p game
cp build-windows/MINIJAM.exe game/
cp $(x86_64-w64-mingw32-gcc -print-file-name=libgcc_s_seh-1.dll) game/
cp $(x86_64-w64-mingw32-gcc -print-file-name=libstdc++-6.dll) game/
cp $(x86_64-w64-mingw32-gcc -print-file-name=libwinpthread-1.dll) game/
cp -r assets/ game/
zip -r game.zip game/
rm -rf game/