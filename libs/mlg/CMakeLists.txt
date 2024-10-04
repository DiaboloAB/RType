cmake_minimum_required(VERSION 3.10)

project(mlg VERSION 0.1)

# header only library
add_library(mlg_lib INTERFACE)


target_include_directories(mlg_lib INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_library(mlg::mlg ALIAS mlg_lib)


# enable_testing()

# add_executable(test_mlg
#     tests/test_basic.cpp
#     )

# target_link_libraries(test_mlg PRIVATE gtest gtest_main mlg)

# add_test(NAME MLGTest COMMAND test_mlg)

