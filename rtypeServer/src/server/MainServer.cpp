/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "MainServer.hpp"

namespace RType::Network {
MainServer::MainServer(std::string host, unsigned int port) : 
    dimension::AServer(std::make_shared<dimension::PacketFactory>(), host, port) {}

MainServer::~MainServer() {}

void MainServer::startRoom(std::string roomCode) {
    if (this->_privateRooms.find(roomCode) != this->_privateRooms.end()) {
        dimension::RoomState &state = this->_privateRooms.find(roomCode)->second;
        std::cerr << "\x1B[32m[MainServer]\x1B[0m: init private room";
    }
    if (this->_privateRooms.find(roomCode) != this->_privateRooms.end()) {
        dimension::RoomState &state = this->_privateRooms.find(roomCode)->second;
        std::cerr << "\x1B[32m[MainServer]\x1B[0m: init room";
    }
}
}
