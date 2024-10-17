cmake_minimum_required(VERSION 3.10)

project(dimension VERSION 0.1)

set(SOURCES
    src/packet/APacket.cpp
    src/packet/PacketManager.cpp
    )

add_library(dimension_lib STATIC ${SOURCES})

target_include_directories(dimension_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/packet
)

add_library(dimension::dimension ALIAS dimension_lib)
