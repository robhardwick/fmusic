# Static Library
add_library(libevomu STATIC
    Player.cpp
    Song.cpp
)

# Link LuaJIT and RtMidi
target_link_libraries(libevomu ${LUAJIT_LIBRARIES})
target_link_libraries(libevomu ${RTMIDI_LIBRARIES})
