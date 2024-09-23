cmake_minimum_required(VERSION 3.10)

project(RTypeECS VERSION 0.1)

set(SOURCES
    src/RTypeECS.cpp
    src/entity/EntityManager.cpp
    src/component/ComponentManager.cpp
    src/component/ComponentArray.cpp
    )

add_library(RTypeECS STATIC ${SOURCES})

target_include_directories(RTypeECS PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/entity
    ${CMAKE_CURRENT_SOURCE_DIR}/src/component
    )

enable_testing()

add_executable(test_ecs
    tests/test_basic.cpp
    tests/test_entity.cpp
    )

target_link_libraries(test_ecs PRIVATE gtest gtest_main RTypeECS)

add_test(NAME ECSTest COMMAND test_ecs)

