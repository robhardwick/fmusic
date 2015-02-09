cmake_minimum_required(VERSION 2.8.11)

project(EvoMu)

# Warnings as errors, use C++11 and set modules path
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall -std=c++11")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

# Enable testing
enable_testing()

# LuaJIT
find_package(LuaJIT)
include_directories(${LUAJIT_INCLUDE_DIR})

# RtMidi
find_package(RtMidi)
include_directories(${RTMIDI_INCLUDE_DIR})

# Build static library, QT app and tests
add_subdirectory(app)
add_subdirectory(lib)
add_subdirectory(tests)
