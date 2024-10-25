cmake_minimum_required(VERSION 3.10)

find_package(SFML REQUIRED COMPONENTS network window graphics system audio)

project(sfml_lib VERSION 0.1)

set(SOURCES
    src/sfml_lib/RenderSystemSFML.cpp
    )

add_library(sfml_lib STATIC ${SOURCES})

target_include_directories(sfml_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include
)

target_link_libraries(sfml_lib PUBLIC
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
    mlg::mlg
)

add_library(sfml_lib::sfml_lib ALIAS sfml_lib)
