pushd emsdk
./emsdk install latest
./emsdk activate latest
source "./emsdk_env.sh"
EMSDK_PATH=$EMSDK
popd

pushd raylib
pushd src
rm *.o
rm libraylib.a
make PLATFORM=PLATFORM_WEB -B
popd
popd

rm -r bin/surge

mkdir bin
mkdir bin/surge

emcc -o bin/surge/index.html src/engine.cpp -Os -Wall raylib/src/libraylib.a  \
    -I raylib/src -I src/header  -Lraylib/src/libraylib.a -s USE_GLFW=3 -s ASSERTIONS=1 -s ALLOW_MEMORY_GROWTH=1 \
    --shell-file src/shell_minimal.html --emrun --preload-file arts -DPLATFORM_WEB