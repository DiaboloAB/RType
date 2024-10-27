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
        [this](asio::ip::udp::endpoint &sender, std::string &desc) { return this->_roomManager.initRoom(sender, desc); });
    this->registerEventHandling("join",
        [this](asio::ip::udp::endpoint &sender, std::string &desc) { return this->_roomManager.joinRoom(sender, desc); });
    this->registerEventHandling("start",
        [this](asio::ip::udp::endpoint &sender, std::string &desc) { return this->_roomManager.startRoom(sender, desc); });
    this->registerEventHandling("end",
        [this](asio::ip::udp::endpoint &sender, std::string &desc) { return this->_roomManager.endRoom(sender, desc); });
    this->registerEventHandling("leave",
        [this](asio::ip::udp::endpoint &sender, std::string &desc) { return this->_roomManager.leaveRoom(sender, desc); });
}

MainServer::~MainServer() {}

void MainServer::handleHiServer(std::pair<std::shared_ptr<dimension::APacket>, asio::ip::udp::endpoint> &packet)
{
    auto hiClient = this->_packetFactory->createEmptyPacket<dimension::HiClient>();
    if (!this->isConnected(packet.second))
    {
        this->_connectedEp.emplace_back(packet.second);
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
}
