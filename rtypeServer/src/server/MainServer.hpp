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
    struct RoomState
    {
        unsigned int _port;
        int _nbConnected = 0;
        std::list<asio::ip::udp::endpoint> _endpoints;
        bool _inGame = false;
        std::shared_ptr<std::thread> _roomThread = nullptr;
    };

    class MainServer : public dimension::AServer {
        public:
            MainServer(std::string host, unsigned int port);
            ~MainServer();
        private:
            void initRoom(asio::ip::udp::endpoint &sender, std::string &description);
            void joinRoom(asio::ip::udp::endpoint &sender, std::string &description);
            void endRoom(asio::ip::udp::endpoint &sender, std::string &description);
            void startRoom(asio::ip::udp::endpoint &sender, std::string &description);
        private:
            unsigned int getAvaiblePort() const;
            std::string generateRoomCode() const;
        private:
            std::unordered_map<std::string, RoomState> _rooms;
            std::unordered_map<std::string, RoomState> _privateRooms;

    };
}
