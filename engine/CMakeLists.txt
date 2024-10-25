cmake_minimum_required(VERSION 3.10)

project(Holtzman VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(ASSETS_PATH "assets/" CACHE STRING "Path to assets directory")

cmake_policy(SET CMP0091 NEW)

find_package(nlohmann_json REQUIRED)
find_package(lua REQUIRED)
find_package(asio REQUIRED)
add_subdirectory(libs/mobs)
add_subdirectory(libs/mlg)
add_subdirectory(libs/dimension)

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

set(SOURCES
src/RTypeEngine.cpp
src/gameContext/GameContext.cpp
src/system/SystemManager.cpp
src/common/animations/Animation.cpp
    src/common/animations/AnimationList.cpp
    
    src/sceneManager/SceneManager.cpp
    src/sceneManager/createEntity.cpp
    src/sceneManager/addScriptsToEntity.cpp
    src/sceneManager/initCppScriptCreators.cpp
    src/clocksManager/ClockManager.cpp
    
    src/addSystems.cpp
    # src/NetworkEvents/NetworkEventHandler.cpp
    src/lua/getKey.cpp
    src/utils/hexaColorToVec3.cpp
    )
    
    add_library(Holtzman STATIC ${SOURCES})
    
    target_include_directories(Holtzman PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    )
    
    target_link_libraries(Holtzman PUBLIC
    nlohmann_json::nlohmann_json
    lua::lua
    asio::asio
    mlg::mlg
    mobs::mobs
    dimension::dimension
    ${GRAPHICS_LIB}
    )

target_compile_definitions(Holtzman PUBLIC ASSETS_PATH="${ASSETS_PATH}")
# add_library(holtzman::holtzman ALIAS holtzman_lib)

option(TESTS "Build tests" OFF)

if (TESTS)

    enable_testing()

    add_executable(test_holtzman tests/test_basic.cpp)

    target_link_libraries(test_holtzman PRIVATE gtest gtest_main Holtzman)

    add_test(NAME HoltzmanTest COMMAND test_holtzman)

endif()
