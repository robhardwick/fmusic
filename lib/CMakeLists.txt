# LuaJIT
find_package(LuaJIT)
include_directories(${LUAJIT_INCLUDE_DIR})

# RtMidi
find_package(RtMidi)
include_directories(${RTMIDI_INCLUDE_DIR})

# Static Library
add_library(libevomu STATIC
    Player.cpp
    Song.cpp
)

target_link_libraries(libevomu ${LUAJIT_LIBRARIES})
target_link_libraries(libevomu ${RTMIDI_LIBRARIES})
