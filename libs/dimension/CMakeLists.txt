cmake_minimum_required(VERSION 3.10)

project(dimension VERSION 0.1)

set(SOURCES
    )

add_library(dimension_lib STATIC ${SOURCES})

target_include_directories(dimension_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_library(dimension ALIAS dimension_lib)
