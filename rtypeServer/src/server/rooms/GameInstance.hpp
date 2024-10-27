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
class GameInstance {
    public:
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
        void run() { if (this->_engine) this->_engine->run(); };
    private:
        std::shared_ptr<Engine> _engine = nullptr;
};
}
