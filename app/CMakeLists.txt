# LuaJIT
find_package(LuaJIT)
include_directories(${LUAJIT_INCLUDE_DIR})
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pagezero_size 10000 -image_base 100000000")

# RtMidi
find_package(RtMidi)
include_directories(${RTMIDI_INCLUDE_DIR})

# QT
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
find_package(Qt5Widgets)
include_directories(${Qt5Widgets_INCLUDE_DIRS})

# Resources / Icon
qt5_add_resources(EvoMu_RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/share/evomu.qrc)

set(MACOSX_BUNDLE_ICON_FILE EvoMu.icns)
set(EvoMu_ICON ${CMAKE_CURRENT_SOURCE_DIR}/share/EvoMu.icns)
set_source_files_properties(${EvoMu_ICON} PROPERTIES
    MACOSX_PACKAGE_LOCATION "Resources")

# App
include_directories(${PROJECT_SOURCE_DIR}/lib)

add_executable(EvoMu MACOSX_BUNDLE
    ${EvoMu_RESOURCES}
    ${EvoMu_ICON}
    main.cpp
    App.cpp
    PlayerWindow.cpp
    Log.cpp
    LogWindow.cpp)

# Link static library and QT
target_link_libraries(EvoMu libevomu)
target_link_libraries(EvoMu ${Qt5Widgets_LIBRARIES})