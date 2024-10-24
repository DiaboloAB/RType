cmake_minimum_required(VERSION 3.10)

project(RType VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(BINARY_NAME "r-type_client")

##############graphic library flag (default sfml)###################
if(NOT DEFINED GRAPHICS)
    set(GRAPHICS "SFML" CACHE STRING "Select the graphics library: SFML, SDL, or OFF" FORCE)
endif()

set_property(CACHE GRAPHICS PROPERTY STRINGS SFML SDL OFF)
######################################################

if(GRAPHICS STREQUAL "SFML")
    message(STATUS "Using SFML as the graphics library")
    add_subdirectory(libs/sfml_lib)
    set(GRAPHICS_LIB sfml_lib::sfml_lib)
    add_definitions(-DGRAPHICS_SFML)
elseif(GRAPHICS STREQUAL "SDL")
    message(STATUS "Using SDL2 as the graphics library")
    add_subdirectory(libs/sdl_lib)
    set(GRAPHICS_LIB sdl_lib::sdl_lib)
    add_definitions(-DGRAPHICS_SDL)
elseif(GRAPHICS STREQUAL "OFF")
    message(STATUS "Using internal graphics handling (no external library)")
    set(GRAPHICS_LIB "")
    add_definitions(-DGRAPHICS_OFF)
else()
    message(FATAL_ERROR "Invalid option for GRAPHICS: ${GRAPHICS}. Use SFML, SDL, or OFF.")
endif()

add_subdirectory(engine)
add_subdirectory(libs/mobs)
add_subdirectory(libs/mlg)

add_executable(${BINARY_NAME}
    src/main.cpp
)

target_include_directories(${BINARY_NAME} PUBLIC
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/engine/src"
)

target_link_libraries(${BINARY_NAME} PRIVATE
    RTypeEngine
    mobs::mobs
    mlg::mlg
    ${GRAPHICS_LIB}
)

set_target_properties(${BINARY_NAME}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../"
)

include(CPack)
