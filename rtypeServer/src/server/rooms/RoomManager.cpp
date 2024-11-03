/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "RoomManager.hpp"
#include "MainServer.hpp"

namespace RType::Network {
RoomManager::RoomManager(MainServer &server, std::shared_ptr<dimension::PacketFactory> factory) : 
    _mainServer(server), _packetFactory(factory) {}

RoomManager::~RoomManager() {}

void RoomManager::initRoom(asio::ip::udp::endpoint &sender, std::string &description)
{
    if (getRoomFromSender(sender) != "") return;
    RoomState roomState;
    std::string roomCode = this->generateRoomCode();
    roomState._endpoints.push_back(sender);
    roomState._nbConnected += 1;
    roomState._port = this->getAvaiblePort();
    if (description != "create=pv" && description != "create=rd") {
        ERR_LOG("RoomManager", "Invalid room creation command.");
        return;
    }
    if (description == "create=pv") this->_privateRooms[roomCode] = roomState;
    else if (description == "create=rd") this->_rooms[roomCode] = roomState;
    this->_clientRooms[sender] = roomCode;
    auto update = _packetFactory->createEmptyPacket<dimension::UpdateEntity>();
    update->setDescription("state:" + roomCode + ":" + std::to_string(1));
    this->_mainServer.send(update, sender);
    LOG("RoomManager", "New room created -> " + roomCode);
}

void RoomManager::joinRoom(asio::ip::udp::endpoint &sender, std::string &description)
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
                auto update = _packetFactory->createEmptyPacket<dimension::UpdateEntity>();
                update->setDescription("state:" + code + ":" + std::to_string(pvRoom.second._nbConnected));
                for (auto &endp : pvRoom.second._endpoints)
                    this->_mainServer.send(update, endp);
                LOG("RoomManager", "Private room joined -> " + pvRoom.first);
                return;
            }
    } else {
        joinRandom(sender);
    }
    //SEND FAILURE
}

void RoomManager::joinRandom(asio::ip::udp::endpoint &sender)
{
    for (auto &rdRoom : this->_rooms) {
        if (rdRoom.second._nbConnected < 4 && !rdRoom.second._inGame) {
            rdRoom.second._endpoints.push_back(sender);
            rdRoom.second._nbConnected += 1;
            this->_clientRooms[sender] = rdRoom.first;
            auto update = _packetFactory->createEmptyPacket<dimension::UpdateEntity>();
            update->setDescription("state:" + rdRoom.first + ":" + std::to_string(rdRoom.second._nbConnected));
            for (auto &endp : rdRoom.second._endpoints)
                this->_mainServer.send(update, endp);
            LOG("RoomManager", "Random room joined -> " + rdRoom.first);
            return;
        }
    }
    std::string initCmd = "create=rd";
    this->initRoom(sender, initCmd);
}

void RoomManager::startRoom(asio::ip::udp::endpoint &sender, std::string &description)
{
    std::string roomCode = this->getRoomFromSender(sender);
    if (roomCode == "") return;
    RoomState &state = getRoomStateFromCode(roomCode);
    if (state._inGame) return;
    state._inGame = true;
    state._gameInstance = std::make_shared<GameInstance>(this->_host, state._port, roomCode);
    state._roomThread = std::make_shared<std::thread>([&state]() { state._gameInstance->run(); });
    auto update = this->_packetFactory->createEmptyPacket<dimension::UpdateEntity>();
    update->setNetworkId(0);
    update->setDescription("room:" + this->_host + ":" + std::to_string(state._port) + ":" + roomCode);
    for (auto &endp : state._endpoints)
        this->_mainServer.send(update, endp);
}

void RoomManager::endRoom(asio::ip::udp::endpoint &sender, std::string &description)
{
    std::string roomCode = getRoomFromSender(sender);
    if (roomCode == "") return;
    RoomState &state = this->getRoomStateFromCode(roomCode);
    if (state._roomThread) {
        state._gameInstance->stop();
        while(!state._roomThread->joinable());
        state._roomThread->join();
    }
    for (auto &endp : state._endpoints) {
        this->_clientRooms[endp] = "";
        this->_mainServer.resetPing(sender);
    }
    return this->deleteRoomFromCode(roomCode);
}

void RoomManager::leaveRoom(asio::ip::udp::endpoint &sender, std::string &description)
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
        LOG("RoomManager", "Player leave room " + roomCode + " (" + 
            std::to_string(state._nbConnected) + " left)");
        this->_clientRooms[sender] = "";
    }
}

std::string RoomManager::generateRoomCode() const
{
    const std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::string roomCode;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, chars.size() - 1);
    for (int i = 0; i < 6; i++) roomCode += chars[distrib(gen)];
    return roomCode;
}

unsigned int RoomManager::getAvaiblePort() const
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

std::string RoomManager::getRoomFromSender(asio::ip::udp::endpoint &sender) const
{
    if (this->_clientRooms.find(sender) != this->_clientRooms.end())
        return this->_clientRooms.at(sender);
    return "";
}

RoomState &RoomManager::getRoomStateFromCode(std::string roomCode)
{
    if (this->_rooms.find(roomCode) != this->_rooms.end())
        return this->_rooms.at(roomCode);
    return this->_privateRooms.at(roomCode);
}

void RoomManager::deleteRoomFromCode(std::string roomCode)
{
    if (this->_rooms.find(roomCode) != this->_rooms.end())
        this->_rooms.erase(roomCode);
    else if (this->_privateRooms.find(roomCode) != this->_privateRooms.end())
        this->_privateRooms.erase(roomCode);
    LOG("RoomManager", "Room " + roomCode + " deleted");
}
}