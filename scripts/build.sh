#!/bin/bash
set -e

# Path
BUILD="./build"

# Remove build dir and exit
if [[ $1 == "clean" ]]; then
    rm -r $BUILD
    exit
fi

# Create build dir
if [ ! -d "$BUILD" ]; then
    mkdir $BUILD
fi

# Build
cmake -B$BUILD -H. -DCMAKE_BUILD_TYPE=debug
make --directory=$BUILD

if [[ $1 == "test" ]]; then
    # Run tests
    CTEST_OUTPUT_ON_FAILURE=TRUE make --directory=$BUILD test
else
    # Run app
    $BUILD/app/EvoMu.app/Contents/MacOS/EvoMu;
fi
