cmake_minimum_required(VERSION 2.8.7)

project(EvoMu)

# Position independent, warnings as errors and C++11
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-fPIC -Wall -std=c++11")

# Enable testing
enable_testing()

# Build static library, QT app and tests
add_subdirectory(app)
add_subdirectory(lib)
add_subdirectory(tests)
