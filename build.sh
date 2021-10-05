#!/bin/bash

pushd raylib\src
make PLATFORM=PLATFORM_DESKTOP
popd

mkdir bin
pushd bin
g++ ../src/engine.cpp -o SpaceEvaders.exe -I ../src/ -I ../raylib/src/ -ggdb -L ../raylib/src/ -lraylib -lopengl32 -lgdi32 -lwinmm  
popd