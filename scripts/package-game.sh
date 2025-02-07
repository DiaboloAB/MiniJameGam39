#!/bin/bash

echo "Packaging game for Windows..."

mkdir -p game
cp build-windows/MINIJAM.exe game/
cp /usr/x86_64-w64-mingw32/bin/*.dll game/
cp -r assets/ game/
zip -r game.zip game/
rm -rf game/