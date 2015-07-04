# Fix linked LuaJIT on OS X (via libfmusic)
if(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pagezero_size 10000 -image_base 100000000")
endif()

# Use includes from lib
include_directories(${PROJECT_SOURCE_DIR}/lib)

# CLI
add_executable(fmu main.cpp)

# Link static library
target_link_libraries(fmu libfmusic)
