# Fix linked LuaJIT on OS X (via libfmusic)
if(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pagezero_size 10000 -image_base 100000000")
endif()

# QT
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
find_package(Qt5Widgets PATHS ${FMUSIC_QT_PATHS})
include_directories(${Qt5Widgets_INCLUDE_DIRS})

# Resources
qt5_add_resources(fMusic_RESOURCES ${PROJECT_SOURCE_DIR}/share/fMusic.qrc)

# Icon
set(MACOSX_BUNDLE_ICON_FILE fMusic.icns)
set(fMusic_ICON ${PROJECT_SOURCE_DIR}/share/fMusic.icns)
set_source_files_properties(${fMusic_ICON} PROPERTIES
    MACOSX_PACKAGE_LOCATION "Resources")

# Use includes from lib
include_directories(${PROJECT_SOURCE_DIR}/lib)

# App
add_executable(fMusic MACOSX_BUNDLE
    ${fMusic_RESOURCES}
    ${fMusic_ICON}
    main.cpp
    App.cpp
    PlayerWindow.cpp
    SyntaxHighlight.cpp
    VisualiserWindow.cpp
    VisualiserCanvas.cpp
    LogWindow.cpp
    SettingsWindow.cpp
    Settings.h)

# Link static library
target_link_libraries(fMusic libfmusic)

# Link QT modules
qt5_use_modules(fMusic Widgets OpenGL)
