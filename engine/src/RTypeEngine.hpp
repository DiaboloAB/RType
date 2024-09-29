/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#pragma once

    #include "RTypeECS.hpp"
    #include "gameContext/GameContext.hpp"
    #include "system/SystemManager.hpp"
    #include "NetworkHandler/NetworkHandler.hpp"
// std
    #include <iostream>
    #include <chrono>

namespace RType {
    class Engine {
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
            Network::NetworkHandler _networkHandler;

    // Member variables
    };
}  // namespace RType
