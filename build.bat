@echo off

pushd raylib\src
rm *.o
rm libraylib.a
mingw32-make PLATFORM=PLATFORM_DESKTOP -B
popd

rm -r bin
mkdir bin
cp -r arts bin/arts
pushd bin
g++ ../src/engine.cpp -o SpaceEvaders.exe -I ../src/ -I ../src/header/ ^
    -I ../raylib/src/ -ggdb -L ../raylib/src/ -lraylib -lopengl32 -lgdi32 -lwinmm  
popd