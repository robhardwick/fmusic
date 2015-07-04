cmake_minimum_required(VERSION 2.8.7)

project(fMusic)

# Set QT search paths for OS X (homebrew) and Linux (local build)
set(FMUSIC_QT_PATHS "/usr/local/opt/qt5" "/usr/local/Qt-5.4.2")

# Position independent, warnings as errors and C++11
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-fPIC -Wall -std=c++11")

# Enable testing
enable_testing()

# Build static library, cli, QT app and tests
add_subdirectory(lib)
add_subdirectory(cli)
add_subdirectory(app)
add_subdirectory(tests)
