cmake_minimum_required(VERSION 3.10)

project(RTypeECS VERSION 0.1)

set(SOURCES src/RTypeECS.cpp)

add_library(RTypeECS STATIC ${SOURCES})

target_include_directories(RTypeECS PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# enable_testing()

# add_executable(test_ tests/test_basic.cpp)

# target_link_libraries(test_ecs PRIVATE gtest gtest_main RTypeECS)

# add_test(NAME ECSTest COMMAND test_ecs)

