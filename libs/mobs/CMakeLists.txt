cmake_minimum_required(VERSION 3.10)

project(mobs VERSION 0.1)

set(SOURCES
    src/mobs/mobs.cpp
    src/mobs/entity/EntityManager.cpp
    src/mobs/component/ComponentManager.cpp
    src/mobs/component/ComponentArray.cpp
    )

add_library(mobs_lib STATIC ${SOURCES})

target_include_directories(mobs_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_library(mobs::mobs ALIAS mobs_lib)

option(TESTS "Build tests" OFF)

if (TESTS)

    enable_testing()

    add_executable(test_mobs
        tests/test_entity.cpp
        )

    target_link_libraries(test_mobs PRIVATE gtest gtest_main mobs_lib)

    add_test(NAME ECSTest COMMAND test_mobs)

endif()
