cmake_minimum_required(VERSION 3.10)

project(RTypeEngine VERSION 0.1)

set(SOURCES src/RTypeEngine.cpp src/RenderSystem/RenderSystem.cpp)

add_library(RTypeEngine STATIC ${SOURCES})

target_include_directories(RTypeEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

enable_testing()

add_executable(test_engine tests/test_basic.cpp)

target_link_libraries(test_engine PRIVATE gtest gtest_main RTypeEngine)

add_test(NAME EngineTest COMMAND test_engine)