/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#pragma once

#include <mlg/mlg.hpp>

#include "NetworkHandler/NetworkHandler.hpp"
#include "clocksManager/ClockManager.hpp"
#include "gameContext/GameContext.hpp"
#include "system/SystemManager.hpp"
// std
#include <chrono>
#include <iostream>

namespace RType
{
/**
 * @class Engine
 * @brief Manages the main game engine, including network handling, runtime, registry, systems,
 * scenes, and clocks.
 */
class Engine
{
   public:
    /**
     * @brief Constructs a new Engine object.
     */
    Engine();

    /**
     * @brief Constructs a new Engine object with network parameters.
     *
     * @param host The host address for the network.
     * @param port The port number for the network.
     * @param isServer Boolean indicating if this instance is a server.
     */
    Engine(std::string host, unsigned int port, bool isServer);

    /**
     * @brief Destroys the Engine object.
     */
    ~Engine();

    /**
     * @brief Runs the game engine.
     */
    void run();

   private:
    std::shared_ptr<Network::NetworkHandler> _networkHandler =
        nullptr;  ///< Network handler for managing network connections.
    std::shared_ptr<IRuntime> _runtime = nullptr;  ///< Shared pointer to the runtime system.

    mobs::Registry _registry;      ///< Entity-component registry.
    SystemManager _systemManager;  ///< Manager for handling various systems.
    SceneManager _sceneManager;    ///< Manager for handling scenes.
    GameContext _gameContext;      ///< Context for managing game state.
    ClockManager _clockManager;    ///< Manager for handling clocks and timing.
    bool _graphical = true;        ///< Boolean indicating if the engine is graphical.
};
}  // namespace RType
