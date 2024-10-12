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
