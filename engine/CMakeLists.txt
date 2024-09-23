cmake_minimum_required(VERSION 3.10)

project(RTypeLibrary)

set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)

set(SOURCES src/RType.cpp)

add_library(RType STATIC ${SOURCES}
)

target_include_directories(RType PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_custom_target(clean
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}
    COMMAND ${CMAKE_COMMAND} -E remove_directory CMakeFiles
    COMMAND ${CMAKE_COMMAND} -E remove CMakeCache.txt cmake_install.cmake Makefile
    COMMENT "Cleaning all build files"
)