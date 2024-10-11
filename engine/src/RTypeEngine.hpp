/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#pragma once

#include <mlg/mlg.hpp>

#include "NetworkHandler/NetworkHandler.hpp"
#include "gameContext/GameContext.hpp"
#include "system/SystemManager.hpp"
#include "clocksManager/ClockManager.hpp"
// std
#include <chrono>
#include <iostream>

namespace RType
{
class Engine
{
   public:
    Engine();
    Engine(std::string host, unsigned int port, bool isServer);
    ~Engine();

    void run();
    void runServer();

   private:

    std::shared_ptr<Network::NetworkHandler> _networkHandler = nullptr;
    std::shared_ptr<IRuntime> _runtime = nullptr;

    mobs::Registry _registry;
    SystemManager _systemManager;
    SceneManager _sceneManager;
    GameContext _gameContext;
    ClockManager _clockManager;
    bool _isServer = false;
};
}  // namespace RType
