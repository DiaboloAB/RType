cmake_minimum_required(VERSION 3.10)

find_package(SFML REQUIRED COMPONENTS network window graphics system)

project(sfml_lib VERSION 0.1)

set(SOURCES
    src/RenderSystemSFML.cpp
    )

add_library(sfml_lib SHARED ${SOURCES})

# Specify the output directory for the shared library (.so)
set_target_properties(sfml_lib PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../../lib
)

target_include_directories(sfml_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(sfml_lib PUBLIC
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
)

add_library(sfml_lib::sfml_lib ALIAS sfml_lib)

option(TESTS "Build tests" OFF)

if (TESTS)

    enable_testing()

    add_executable(test_sfml
        tests/*.cpp
        )

    target_link_libraries(test_sfml PRIVATE gtest gtest_main sfml_lib)

    add_test(NAME SFMLtest COMMAND test_sfml)

endif()
