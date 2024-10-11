cmake_minimum_required(VERSION 3.10)

project(RTypeEngine VERSION 0.1)

find_package(SFML REQUIRED COMPONENTS network window graphics system)
find_package(nlohmann_json REQUIRED)
find_package(lua REQUIRED)
find_package(asio REQUIRED)

set(SOURCES
    src/RTypeEngine.cpp
    src/RenderSystemSFML/RenderSystemSFML.cpp
    src/gameContext/GameContext.cpp
    src/system/SystemManager.cpp
    src/common/animations/Animation.cpp
    src/common/animations/AnimationList.cpp
    src/NetworkHandler/NetworkHandler.cpp
    src/NetworkHandler/PacketHandler.cpp
    src/sceneManager/SceneManager.cpp
    src/sceneManager/createEntity.cpp
    src/sceneManager/addScriptsToEntity.cpp
    src/sceneManager/initComponentCreators.cpp
    src/sceneManager/initCppScriptCreators.cpp
    src/clocksManager/ClockManager.cpp
    src/PacketManager/APacket.cpp
    src/PacketManager/AdiosServerPacket.cpp
    src/PacketManager/ClientEventPacket.cpp
    src/PacketManager/CreateEntityPacket.cpp
    src/PacketManager/DestroyEntityPacket.cpp
    src/PacketManager/PingPacket.cpp
    src/PacketManager/HiClientPacket.cpp
    src/PacketManager/HiServerPacket.cpp
    src/PacketManager/KickClientPacket.cpp
    src/PacketManager/MoveEntityPacket.cpp
    src/PacketManager/PacketFactory.cpp
    src/PacketManager/PacketValidationPacket.cpp
    src/PacketManager/UpdateEntityPacket.cpp
    src/lua/getKey.cpp
    src/utils/hexaColorToVec3.cpp
    )

add_library(RTypeEngine STATIC ${SOURCES})

target_include_directories(RTypeEngine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    )

target_link_libraries(RTypeEngine PUBLIC
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
    nlohmann_json::nlohmann_json
    lua::lua
    asio::asio
    mlg::mlg
    mobs::mobs
)

enable_testing()

add_executable(test_engine tests/test_basic.cpp)

target_link_libraries(test_engine PRIVATE gtest gtest_main RTypeEngine)

add_test(NAME EngineTest COMMAND test_engine)