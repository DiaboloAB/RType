/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "MainServer.hpp"

namespace RType::Network {
MainServer::MainServer(std::string host, unsigned int port) : 
    dimension::AServer(std::make_shared<dimension::PacketFactory>(), host, port) 
{
    this->registerEventHandling("create",
        [this](asio::ip::udp::endpoint &sender, std::string &desc) { return this->initRoom(sender, desc); });
    this->registerEventHandling("join",
        [this](asio::ip::udp::endpoint &sender, std::string &desc) { return this->joinRoom(sender, desc); });
    this->registerEventHandling("start",
        [this](asio::ip::udp::endpoint &sender, std::string &desc) { return this->startRoom(sender, desc); });
    this->registerEventHandling("end",
        [this](asio::ip::udp::endpoint &sender, std::string &desc) { return this->endRoom(sender, desc); });
    this->registerEventHandling("leave",
        [this](asio::ip::udp::endpoint &sender, std::string &desc) { return this->leaveRoom(sender, desc); });
}

MainServer::~MainServer() {}

void MainServer::initRoom(asio::ip::udp::endpoint &sender, std::string &description)
{
    if (getRoomFromSender(sender) != "") return;
    RoomState roomState;
    std::string roomCode = this->generateRoomCode();
    roomState._endpoints.push_back(sender);
    roomState._nbConnected += 1;
    roomState._port = this->getAvaiblePort();
    if (description != "create=pv" && description != "create=rd") {
        ERR_LOG("MainServer", "Invalid room creation command.");
        return;
    }
    if (description == "create=pv") this->_privateRooms[roomCode] = roomState;
    else if (description == "create=rd") this->_rooms[roomCode] = roomState;
    this->_clientRooms[sender] = roomCode;
    LOG("MainServer", "New room created -> " + roomCode);
}

void MainServer::joinRoom(asio::ip::udp::endpoint &sender, std::string &description)
{
    if (this->getRoomFromSender(sender) != "") return;
    std::size_t posSeparator = description.find('=');
    std::string code = description.substr(posSeparator + 1);
    if (code != "rd") {
        for (auto &pvRoom : this->_privateRooms)
            if (pvRoom.first == code && pvRoom.second._nbConnected < 4 && 
                !pvRoom.second._inGame) {
                pvRoom.second._nbConnected += 1;
                pvRoom.second._endpoints.push_back(sender);
                this->_clientRooms[sender] = code;
                LOG("MainServer", "Private room joined -> " + pvRoom.first);
                return;
            }
    } else {
        joinRandom(sender);
    }
    //SEND FAILURE
}

void MainServer::joinRandom(asio::ip::udp::endpoint &sender)
{
    for (auto &rdRoom : this->_rooms) {
        if (rdRoom.second._nbConnected < 4 && !rdRoom.second._inGame) {
            rdRoom.second._endpoints.push_back(sender);
            rdRoom.second._nbConnected += 1;
            this->_clientRooms[sender] = rdRoom.first;
            LOG("MainServer", "Random room joined -> " + rdRoom.first);
            return;
        }
    }
    std::string initCmd = "create=rd";
    this->initRoom(sender, initCmd);
}

void MainServer::startRoom(asio::ip::udp::endpoint &sender, std::string &description)
{
    return;
}

void MainServer::endRoom(asio::ip::udp::endpoint &sender, std::string &description)
{
    std::string roomCode = getRoomFromSender(sender);
    if (roomCode == "") return;
    RoomState &state = this->getRoomStateFromCode(roomCode);
    if (state._roomThread) state._roomThread->join();
    for (auto &endp : state._endpoints) {
        this->_clientRooms[endp] = "";
        //this->resendToMenu(endp);
    }
    return this->deleteRoomFromCode(roomCode);
}

void MainServer::leaveRoom(asio::ip::udp::endpoint &sender, std::string &description)
{
    std::string roomCode = getRoomFromSender(sender);
    if (roomCode == "") return;
    RoomState &state = getRoomStateFromCode(roomCode);
    if (state._inGame) return;
    if (state._nbConnected == 1) {
        std::string endCmd = "end=N";
        return this->endRoom(sender, endCmd);
    }
    auto it = std::find(state._endpoints.begin(), state._endpoints.end(), sender);
    if (it != state._endpoints.end()) {
        state._endpoints.erase(it);
        state._nbConnected -= 1;
        LOG("MainServer", "Player leave room " + roomCode + " (" + 
            std::to_string(state._nbConnected) + " left)");
        this->_clientRooms[sender] = "";
        //this->resendToMenu(endp);
    }
}

std::string MainServer::generateRoomCode() const
{
    const std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::string roomCode;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, chars.size() - 1);
    for (int i = 0; i < 6; i++) roomCode += chars[distrib(gen)];
    return roomCode;
}

unsigned int MainServer::getAvaiblePort() const
{
    asio::io_context io_context;
    asio::ip::udp::socket socket(io_context);
    asio::ip::udp::endpoint endpoint(asio::ip::udp::v4(), 0);
    socket.open(endpoint.protocol());
    socket.bind(endpoint);
    unsigned int port = (unsigned int)socket.local_endpoint().port();
    socket.close();
    return port;
}

std::string MainServer::getRoomFromSender(asio::ip::udp::endpoint &sender) const
{
    if (this->_clientRooms.find(sender) != this->_clientRooms.end())
        return this->_clientRooms.at(sender);
    return "";
}

RoomState &MainServer::getRoomStateFromCode(std::string roomCode)
{
    if (this->_rooms.find(roomCode) != this->_rooms.end())
        return this->_rooms.at(roomCode);
    return this->_privateRooms.at(roomCode);
}

void MainServer::deleteRoomFromCode(std::string roomCode)
{
    if (this->_rooms.find(roomCode) != this->_rooms.end())
        this->_rooms.erase(roomCode);
    else if (this->_privateRooms.find(roomCode) != this->_privateRooms.end())
        this->_privateRooms.erase(roomCode);
    LOG("MainServer", "Room " + roomCode + " deleted");
}
}
