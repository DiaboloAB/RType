cmake_minimum_required(VERSION 3.10)

project(dimension VERSION 0.1)

find_package(asio REQUIRED)

set(SOURCES
    src/dimension/packet/APacket.cpp
    src/dimension/packet/PacketManager.cpp
    src/dimension/packet/APacketFactory.cpp
    src/dimension/endpoint/AEndpoint.cpp
    src/dimension/endpoint/client/Client.cpp
    )

add_library(dimension_lib STATIC ${SOURCES})

target_include_directories(dimension_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/dimension
    ${CMAKE_CURRENT_SOURCE_DIR}/src/dimension/packet
    ${CMAKE_CURRENT_SOURCE_DIR}/src/dimension/endpoint
    ${CMAKE_CURRENT_SOURCE_DIR}/src/dimension/endpoint/client
)

target_link_libraries(dimension_lib PUBLIC asio::asio)

add_library(dimension::dimension ALIAS dimension_lib)
