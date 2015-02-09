# QT
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
find_package(Qt5Test)
include_directories(${Qt5Test_INCLUDE_DIRS})

# Use includes from app and lib
include_directories(${PROJECT_SOURCE_DIR}/app)
include_directories(${PROJECT_SOURCE_DIR}/lib)

# Player Tests
add_executable(TestPlayer TestPlayer.cpp)
add_test(TestPlayer TestPlayer)
target_link_libraries(TestPlayer ${Qt5Test_LIBRARIES})
target_link_libraries(TestPlayer libevomu)
