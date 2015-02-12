# Fix linked LuaJIT on OS X (via libevomu)
if(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pagezero_size 10000 -image_base 100000000")
endif()

# QT
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
find_package(Qt5Test)
include_directories(${Qt5Test_INCLUDE_DIRS})

# Use includes from app and lib
include_directories(${PROJECT_SOURCE_DIR}/app)
include_directories(${PROJECT_SOURCE_DIR}/lib)

# Build tests
foreach(TEST_NAME Player Song)

    # Create test
    add_executable(Test${TEST_NAME} Test.cpp Test${TEST_NAME}.cpp)
    add_test(Test${TEST_NAME} Test${TEST_NAME})

    # Link with QT5Test and libevomu
    target_link_libraries(Test${TEST_NAME} ${Qt5Test_LIBRARIES})
    target_link_libraries(Test${TEST_NAME} libevomu)

endforeach()
