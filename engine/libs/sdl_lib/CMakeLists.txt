cmake_minimum_required(VERSION 3.10)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

project(sdl_lib VERSION 0.1)

set(SOURCES
    src/sdl_lib/RenderSystemSDL.cpp
    )

add_library(sdl_lib STATIC ${SOURCES})

target_include_directories(sdl_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include
)

target_link_libraries(sdl_lib PUBLIC
    SDL2::SDL2main
    sdl_ttf::sdl_ttf
    SDL2_mixer::SDL2_mixer
    mlg::mlg
)

add_library(sdl_lib::sdl_lib ALIAS sdl_lib)
