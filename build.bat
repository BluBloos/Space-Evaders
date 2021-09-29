@echo off
mkdir bin
pushd bin
cl -Zi -FeSpaceEvaders ../src/engine.cpp
popd
