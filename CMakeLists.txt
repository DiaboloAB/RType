cmake_minimum_required(VERSION 3.10)

project(RType VERSION 1.0)

# find_package(Asio REQUIRED)
# find_package(glfw3 REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(engine)
add_subdirectory(libs/ecs)


add_executable(RType src/main.cpp)

target_link_libraries(RType PRIVATE
    RTypeEngine
    RTypeECS
    # asio::asio
    # sfml-graphics
    # sfml-audio
    # sfml-network
)

include(CPack)

target_include_directories(RType PUBLIC
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/engine/src"
    "${PROJECT_SOURCE_DIR}/libs/ecs/src"
)

# vvv Testing vvv #

enable_testing()

add_executable(test_basic tests/test_basic.cpp)

target_link_libraries(test_basic PRIVATE gtest gtest_main
    RTypeEngine
    RTypeECS
)

add_test(NAME BasicTest COMMAND test_basic)
