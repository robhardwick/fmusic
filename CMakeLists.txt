cmake_minimum_required(VERSION 2.8.11)

project(EvoMu)

# Warnings as errors, use C++11 and set modules path
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall -std=c++11")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

# Build static library and QT app
add_subdirectory(lib)
add_subdirectory(app)
