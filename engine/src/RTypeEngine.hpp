/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#pragma once

#include <glm/glm.hpp>

#include "NetworkHandler/NetworkHandler.hpp"
#include "RTypeECS.hpp"
#include "common/components.hpp"
#include "gameContext/GameContext.hpp"
#include "system/SystemManager.hpp"
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
    // Getters

    // Setters

   private:
    ECS::Registry _registry;
    SystemManager _systemManager;
    GameContext _gameContext;
   public:
    std::shared_ptr<Network::NetworkHandler> _networkHandler = nullptr;

    // Member variables
};
}  // namespace RType
