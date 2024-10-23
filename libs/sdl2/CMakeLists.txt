cmake_minimum_required(VERSION 3.10)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

project(sdl_lib VERSION 0.1)

set(SOURCES
    src/RenderSystemSDL.cpp
    )

add_library(sdl_lib SHARED ${SOURCES})

# Specify the output directory for the shared library (.so)
set_target_properties(sdl_lib PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../../lib
)

target_include_directories(sdl_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(sdl_lib PUBLIC
    SDL2::SDL2main
    sdl_ttf::sdl_ttf
    SDL2_mixer::SDL2_mixer
)

add_library(sdl_lib::sdl_lib ALIAS sdl_lib)

option(TESTS "Build tests" OFF)

if (TESTS)

    enable_testing()

    add_executable(test_sfml
        tests/*.cpp
        )

    target_link_libraries(test_sfml PRIVATE gtest gtest_main sdl_lib)

    add_test(NAME SFMLtest COMMAND test_sfml)

endif()
