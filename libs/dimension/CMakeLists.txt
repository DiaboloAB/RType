cmake_minimum_required(VERSION 3.10)

project(dimension VERSION 0.1)

find_package(asio REQUIRED)

set(SOURCES
    src/dimension/packet/APacket.cpp
    src/dimension/packet/PacketManager.cpp
    src/dimension/packet/PacketFactory.cpp
    src/dimension/packet/basics/AdiosServer.cpp
    src/dimension/packet/basics/HiServer.cpp
    src/dimension/packet/basics/HiClient.cpp
    src/dimension/packet/basics/CreateEntity.cpp
    src/dimension/packet/basics/DestroyEntity.cpp
    src/dimension/packet/basics/MoveEntity.cpp
    src/dimension/packet/basics/ClientEvent.cpp
    src/dimension/packet/basics/PacketValidation.cpp
    src/dimension/packet/basics/UpdateEntity.cpp
    src/dimension/packet/basics/Ping.cpp
    src/dimension/endpoint/AEndpoint.cpp
    src/dimension/endpoint/client/Client.cpp
    src/dimension/endpoint/server/AServer.cpp
    )

add_library(dimension_lib STATIC ${SOURCES})

target_include_directories(dimension_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/dimension
    ${CMAKE_CURRENT_SOURCE_DIR}/src/dimension/packet
    ${CMAKE_CURRENT_SOURCE_DIR}/src/dimension/packet/basics
    ${CMAKE_CURRENT_SOURCE_DIR}/src/dimension/endpoint
    ${CMAKE_CURRENT_SOURCE_DIR}/src/dimension/room
    ${CMAKE_CURRENT_SOURCE_DIR}/src/dimension/endpoint/client
    ${CMAKE_CURRENT_SOURCE_DIR}/src/dimension/endpoint/server
)

target_link_libraries(dimension_lib PUBLIC asio::asio)

add_library(dimension::dimension ALIAS dimension_lib)
