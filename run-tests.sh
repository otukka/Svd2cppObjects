#!/bin/bash


BUILD_DIR="build"

# Create build folder if not exists
if [ ! -e $BUILD_DIR ]; then
    mkdir build
fi

# Init cmake if not init before. If fails will delete build-folder
if [ "$(ls -A $BUILD_DIR)" ]; then
    cd build
else
    cd build
    
    if cmake -DCMAKE_BUILD_TYPE=Debug -DBUILD_DRIVER=OFF -DBUILD_TESTS=ON -DCMAKE_TOOLCHAIN_FILE=toolchains/i386-linux-gnu.cmake .. ; then 
        echo "success"
    else
        cd ..
        rm -rf build
        exit 1
    fi
fi

make -j`nproc` || exit 1

make tests || exit 1

if [ $# -eq 0 ]; then
    ctest
else
    ctest -R "$1"
fi

