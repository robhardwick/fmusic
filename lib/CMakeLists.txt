# Set cmake modules path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Pthreads
find_package(Threads REQUIRED)

# LuaJIT
find_package(LuaJIT REQUIRED)
include_directories(${LUAJIT_INCLUDE_DIR})

# RtMidi
find_package(RtMidi REQUIRED)
include_directories(${RTMIDI_INCLUDE_DIR})

# Static Library
add_library(libevomu STATIC
    Player.cpp
    Song.cpp
    MIDI.cpp
)

# Link Pthreads, LuaJIT and RtMidi
target_link_libraries(libevomu ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(libevomu ${LUAJIT_LIBRARIES})
target_link_libraries(libevomu ${RTMIDI_LIBRARIES})
