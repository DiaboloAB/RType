cmake_minimum_required(VERSION 3.10)

project(RTypeEngine VERSION 0.1)

find_package(SFML REQUIRED COMPONENTS network window graphics system)
find_package(glm REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(lua REQUIRED)
find_package(asio REQUIRED)

set(SOURCES
    src/RTypeEngine.cpp
    src/RenderSystemSFML/RenderSystemSFML.cpp
    src/gameContext/GameContext.cpp
    src/system/SystemManager.cpp
    src/NetworkHandler/NetworkHandler.cpp
    )

add_library(RTypeEngine STATIC ${SOURCES})

target_include_directories(RTypeEngine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/libs/ecs/src
    )

target_link_libraries(RTypeEngine PUBLIC RTypeECS
    sfml-graphics
    sfml-window
    sfml-system
    glm::glm
    nlohmann_json::nlohmann_json
    lua::lua
    asio::asio
)

enable_testing()

add_executable(test_engine tests/test_basic.cpp)

target_link_libraries(test_engine PRIVATE gtest gtest_main RTypeEngine)

add_test(NAME EngineTest COMMAND test_engine)