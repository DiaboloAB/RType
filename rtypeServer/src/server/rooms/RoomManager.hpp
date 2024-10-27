/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#pragma once

#include <asio.hpp>
#include <string>
#include <unordered_map>
#include <random>

#include "RoomState.hpp"
#include "Logger.hpp"

namespace RType::Network {
class RoomManager {
    public:
        RoomManager();
        ~RoomManager();
    public:
        void initRoom(asio::ip::udp::endpoint &sender, std::string &description);
        void joinRoom(asio::ip::udp::endpoint &sender, std::string &description);
        void joinRandom(asio::ip::udp::endpoint &sender);
        void endRoom(asio::ip::udp::endpoint &sender, std::string &description);
        void startRoom(asio::ip::udp::endpoint &sender, std::string &description);
        void leaveRoom(asio::ip::udp::endpoint &sender, std::string &description);
    public:
        unsigned int getAvaiblePort() const;
        std::string generateRoomCode() const;
        std::string getRoomFromSender(asio::ip::udp::endpoint &sender) const;
        RoomState &getRoomStateFromCode(std:: string code);
        void deleteRoomFromCode(std::string roomCode);
    private:
        std::unordered_map<std::string, RoomState> _rooms;
        std::unordered_map<std::string, RoomState> _privateRooms;
        std::unordered_map<asio::ip::udp::endpoint, std::string> _clientRooms;
};
}