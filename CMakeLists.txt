cmake_minimum_required(VERSION 3.10)

project(RType VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


add_subdirectory(engine)
add_subdirectory(libs/mobs)
add_subdirectory(libs/mlg)
add_subdirectory(libs/sfml)
add_subdirectory(libs/sdl2)

add_executable(r-type_client
    src/main.cpp
)

target_link_libraries(r-type_client PRIVATE
    RTypeEngine
    mobs::mobs
    mlg::mlg
)

include(CPack)

target_include_directories(r-type_client PUBLIC
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/engine/src"
)

set_target_properties(r-type_client
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../"
)
