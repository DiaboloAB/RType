/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#pragma once

#include <mlg/mlg.hpp>
#include <nlohmann/json.hpp>

#include "clocksManager/ClockManager.hpp"
#include "gameContext/GameContext.hpp"
#include "system/SystemManager.hpp"
// std
#include <atomic>
#include <chrono>
#include <iostream>
#include <mutex>

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
    Engine(std::map<std::string, std::string> args = {});

    /**
     * @brief Destroys the Engine object.
     */
    ~Engine();

    /**
     * @brief Runs the game engine.
     */
    void run();

    void stop();

   private:
    void loadGame();

    std::shared_ptr<IRuntime> _runtime = nullptr;         ///< Shared pointer to the runtime system.
    std::shared_ptr<GameContext> _gameContext = nullptr;  ///< Shared pointer to the game context.

    mobs::Registry _registry;      ///< Entity-component registry.
    SystemManager _systemManager;  ///< Manager for handling various systems.
    SceneManager _sceneManager;    ///< Manager for handling scenes.
    ClockManager _clockManager;    ///< Manager for handling clocks and timing.

    std::string _assetsPath = "assets/";       ///< Path to the assets directory.
    std::map<std::string, std::string> _args;  ///< Map of arguments passed to the engine.
    nlohmann::json _gameConfig;                ///< JSON object for storing game configuration.
    std::atomic<bool> _stop = false;
    std::mutex _stopmtx;
};
}  // namespace RType
