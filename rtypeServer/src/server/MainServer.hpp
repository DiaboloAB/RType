/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#pragma once

#include "AServer.hpp"
#include "PacketFactory.hpp"

namespace RType::Network {
    class MainServer : public dimension::AServer {
        public:
            MainServer(std::string host, unsigned int port);
            ~MainServer();
        public:
            void startRoom(std::string roomCode) override;
    };
}
