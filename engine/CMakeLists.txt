cmake_minimum_required(VERSION 3.10)

project(RTypeEngine VERSION 0.1)

set(SOURCES src/RType.cpp)

add_library(RTypeEngine STATIC ${SOURCES})

target_include_directories(RTypeEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
