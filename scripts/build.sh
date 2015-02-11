#!/bin/bash
set -e

# For homebrew on os x
export CMAKE_PREFIX_PATH="/usr/local/opt/qt5:/usr/local/opt/luajit"

# Paths
CWD=`pwd`
BUILD="./build"

# Clean build dir and exit
if [[ $1 == "clean" ]]; then
    rm -r $BUILD
    exit
fi

# Create build dir
if [ ! -d "$BUILD" ]; then
    mkdir $BUILD
fi

# Enter tmp dir and build
cd $BUILD
cmake -DCMAKE_BUILD_TYPE=debug ..
make
cd $CWD

if [[ $1 == "test" ]]; then
    # Run tests
    make -C $BUILD test
else
    # Run app
    $BUILD/app/EvoMu.app/Contents/MacOS/EvoMu;
fi
