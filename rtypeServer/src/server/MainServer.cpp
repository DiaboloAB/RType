/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "MainServer.hpp"

namespace RType::Network {
MainServer::MainServer(std::string host, unsigned int port) : 
    dimension::AServer(std::make_shared<dimension::PacketFactory>(), host, port), _roomManager(*this, this->_packetFactory)
{
    this->registerEventHandling("create",
        [this](asio::ip::udp::endpoint &sender, std::string &desc) { return this->_roomManager.initRoom(sender, desc); });
    this->registerEventHandling("join",
        [this](asio::ip::udp::endpoint &sender, std::string &desc) { return this->_roomManager.joinRoom(sender, desc); });
    this->registerEventHandling("start",
        [this](asio::ip::udp::endpoint &sender, std::string &desc) { return this->_roomManager.startRoom(sender, desc); });
    this->registerEventHandling("end",
        [this](asio::ip::udp::endpoint &sender, std::string &desc) { return this->_roomManager.endRoom(sender, desc); });
    this->registerEventHandling("leave",
        [this](asio::ip::udp::endpoint &sender, std::string &desc) { return this->_roomManager.leaveRoom(sender, desc); });
    this->_roomManager.setHost(this->_host);
}

MainServer::~MainServer() {}

void MainServer::handleHiServer(std::pair<std::shared_ptr<dimension::APacket>, asio::ip::udp::endpoint> &packet)
{
    auto hiClient = this->_packetFactory->createEmptyPacket<dimension::HiClient>();
    if (!this->isConnected(packet.second))
    {
        this->_connectedEp.push_back(std::make_pair(packet.second, std::chrono::steady_clock::now()));
        LOG("AServer", "New connection received.");
    }
    this->send(hiClient, packet.second);
}

void MainServer::handleEvent(std::pair<std::shared_ptr<dimension::APacket>, asio::ip::udp::endpoint> &packet)
{
    if (!isConnected(packet.second)) return;
    try
    {
        std::shared_ptr<dimension::ClientEvent> event = 
            std::dynamic_pointer_cast<dimension::ClientEvent>(packet.first);
        if (event->getClientEvent() != dimension::ClientEventType::ROOM) return;
        std::string eventDesc = event->getDescription();
        size_t pos = eventDesc.find('=');
        if (pos == std::string::npos ||
            this->_eventH.find(eventDesc.substr(0, pos)) == this->_eventH.end())
            ERR_LOG("AServer", "Unknow event {" + eventDesc + "}");
        else
            this->_eventH[eventDesc.substr(0, pos)](packet.second, eventDesc);
        auto validation = this->_packetFactory->createEmptyPacket<dimension::PacketValidation>();
        validation->setPacketReceiveTimeStamp(packet.first->getPacketTimeStamp());
        validation->setPacketReceiveType(packet.first->getPacketType());
        this->send(validation, packet.second, false);
    }
    catch (std::exception &e)
    {
        ERR_LOG("AServer", std::string("Error in client event {") + e.what() + "}");
    }
}

void MainServer::handlePing(std::pair<std::shared_ptr<dimension::APacket>, asio::ip::udp::endpoint> &packet)
{
    std::string room = this->_roomManager.getRoomFromSender(packet.second);
    if (room != "" && this->_roomManager.getRoomStateFromCode(room)._inGame)
        return;
    for (auto &endp : this->_connectedEp)
        if (endp.first == packet.second) {
            endp.second = std::chrono::steady_clock::now();
            return;
        }
}

void MainServer::checkLastPing() {
    std::string leave = "leave=crash";
    for (auto it = this->_connectedEp.begin(); it != this->_connectedEp.end();) {
        std::string room = this->_roomManager.getRoomFromSender(it->first);
        std::chrono::steady_clock::time_point actualTime = std::chrono::steady_clock::now();
        if (room != "" && this->_roomManager.getRoomStateFromCode(room)._inGame) {
            it++;
            continue;
        }
        if (std::chrono::duration_cast<std::chrono::milliseconds>(actualTime - it->second).count() < 4000) {
            it++;
            continue;
        }
        if (room != "") this->_roomManager.leaveRoom(it->first, leave);
        for (auto itV = this->_validationList.begin(); itV != _validationList.end();) {
            if (itV->second._sender == it->first) itV = this->_validationList.erase(itV);
            else itV++;
        }
        ERR_LOG("MainServer", "Client crash");
        it = this->_connectedEp.erase(it);
    }
}

void MainServer::sendPing()
{
    auto pingPacket = this->_packetFactory->createEmptyPacket<dimension::Ping>();
    for (auto &endp : this->_connectedEp) {
        std::string roomCode = this->_roomManager.getRoomFromSender(endp.first);
        if (roomCode == "") this->send(pingPacket, endp.first, false);
        else {
            auto state = this->_roomManager.getRoomStateFromCode(roomCode);
            if (!state._inGame) this->send(pingPacket, endp.first, false);
        }
    }
}

void MainServer::resetPing(asio::ip::udp::endpoint &sender) {
    for (auto &endp : this->_connectedEp) {
        if (endp.first == sender) {
            endp.second = std::chrono::steady_clock::now();
            return;
        }
    }
}
}
