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
#include "GameInstance.hpp"
#include "Logger.hpp"

namespace RType::Network {

class MainServer;

class RoomManager {
    public:
        RoomManager(MainServer &server);
        ~RoomManager();

    public:
        /**
         * @brief Create a room.
         * 
         * @param sender: Endpoint of the client who create the room.
         * @param description: Description of the room (Example: "create=pv" to create a private room).
         */
        void initRoom(asio::ip::udp::endpoint &sender, std::string &description);
        
        /**
         * @brief Join a selected room.
         * 
         * @param sender: Endpoint of the client who join the room.
         * @param description: Description of the room (Example: "join=[CODE]" to join a private room).
         */
        void joinRoom(asio::ip::udp::endpoint &sender, std::string &description);

        /**
         * @brief Join a random opened room.
         * 
         * @param sender: Endpoint of the client who join the room.
         */
        void joinRandom(asio::ip::udp::endpoint &sender);

        /**
         * @brief Stop and delete room if empty or game finished.
         * 
         * @param sender: Endpoint of the last client of the room.
         * @param description: UNUSED PARAMETER.
         */
        void endRoom(asio::ip::udp::endpoint &sender, std::string &description);

        /**
         * @brief Start the game of the room.
         * 
         * @param sender: Endpoint of the client who start the game.
         * @param description: UNUSED PARAMETER.
         */
        void startRoom(asio::ip::udp::endpoint &sender, std::string &description);

        /**
         * @brief Make the client leave the room.
         * 
         * @param sender: Endpoint of the client who leave the room.
         * @param description: UNUSED PARAMETER.
         */
        void leaveRoom(asio::ip::udp::endpoint &sender, std::string &description);

    public:
        unsigned int getAvaiblePort() const;
        std::string getRoomFromSender(asio::ip::udp::endpoint &sender) const;
        RoomState &getRoomStateFromCode(std:: string code);

    public:
        /**
         * @brief Generate a room code with random ASCII capital letters and numbers (Example: WX08F3).
         * 
         * @return std::string 
         */
        std::string generateRoomCode() const;

        /**
         * @brief  Delete a room with the associated code.
         * 
         * @param roomCode: code of the room to delete (Example: WX08F3).
         */
        void deleteRoomFromCode(std::string roomCode);
    
    public:
        void setHost(std::string host) { this->_host = host; };

    private:
        std::string _host = "127.0.0.1";
        std::unordered_map<std::string, RoomState> _rooms;
        std::unordered_map<std::string, RoomState> _privateRooms;
        std::unordered_map<asio::ip::udp::endpoint, std::string> _clientRooms;
        MainServer &_mainServer;
};
}