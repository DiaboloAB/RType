/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#pragma once

#include <string>
#include <RTypeEngine.hpp>

namespace RType::Network {

/**
 * @class GameInstance
 * 
 * @brief GameInstance handles creating threaded game instances by initializing
 * a server-mode engine and providing the option to start it.
 */
class GameInstance {
    public:
        /**
         * @brief Constructs a GameInstance, initializing the engine in server mode.
         *
         * @param host IP address for the game server (e.g., "127.0.0.1")
         * @param port UDP communication port for the game
         * @param code Unique game code for managing client connections
         */
        GameInstance(std::string host, unsigned int port, std::string code) {
            std::map<std::string, std::string> args;
            args["graphics"] = "off";
            args["host"] = host;
            args["port"] = std::to_string(port);
            args["code"] = code;
            this->_engine = std::make_shared<Engine>(args);
        };

        ~GameInstance() {};

    public:
        /**
         * @brief Runs the game engine (suitable for execution in a separate thread).
         */
        void run() { if (this->_engine) this->_engine->run(); };

    private:
        std::shared_ptr<Engine> _engine = nullptr;
};
}
