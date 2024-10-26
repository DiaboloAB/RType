/**********************************************************************************
 *  Project: Dimension Network
 *  Description: Networking Game Library
 *  Author: Morgan LARGEOT, Maxence LARGEOT
 *  Create Time: 2024-10-17
 *  Location: Rennes
 **********************************************************************************/

#include "AServer.hpp"

namespace dimension
{
AServer::AServer(const std::shared_ptr<PacketFactory> &factory, std::string host, unsigned int port)
    : AEndpoint(factory)
{
    this->_packetH[this->_packetFactory->getTypeFromIndex(std::type_index(typeid(ClientEvent)))] =
        [this](std::pair<std::shared_ptr<APacket>, asio::ip::udp::endpoint> pair)
    { return this->handleEvent(pair); };
    this->_packetH[this->_packetFactory->getTypeFromIndex(std::type_index(typeid(HiServer)))] =
        [this](std::pair<std::shared_ptr<APacket>, asio::ip::udp::endpoint> pair)
    { return this->handleHiServer(pair); };
    this->initServer(host, port);
}

void AServer::initServer(std::string host, unsigned int port)
{
    try
    {
        this->_io_context = std::make_shared<asio::io_context>();
        asio::ip::udp::endpoint endpoint(asio::ip::udp::v4(), port);
        this->_socket = std::make_shared<asio::ip::udp::socket>(*this->_io_context, endpoint);
        this->receive();
        this->_recvThread =
            std::make_shared<std::thread>(std::thread([this] { this->_io_context->run(); }));
        std::cerr << "\x1B[32m[AServer]\x1B[0m: Server setup." << std::endl;
    }
    catch (std::exception &e)
    {
        std::cerr << "\x1B[31m[AServer ERROR]\x1B[0m: " << e.what() << std::endl;
    }
}

void AServer::run()
{
    while (true)
    {
        this->resendValidationList();
        std::queue<std::pair<std::shared_ptr<APacket>, asio::ip::udp::endpoint>> queueAtT =
            this->_rcvQueue;
        while (!queueAtT.empty())
        {
            auto &packet = queueAtT.front();
            auto function = this->_packetH.find(packet.first->getPacketType());
            if (!(function == this->_packetH.end())) function->second(packet);
            this->popReceiveQueue();
            queueAtT.pop();
        }
    }
}

void AServer::handleHiServer(std::pair<std::shared_ptr<APacket>, asio::ip::udp::endpoint> &packet)
{
    auto hiClient = this->_packetFactory->createEmptyPacket<HiClient>();
    if (!this->isConnected(packet.second))
    {
        this->_connectedEp.emplace_back(packet.second);
        std::cerr << "\x1B[32m[AServer]\x1B[0m: New connection received." << std::endl;
    }
    this->send(hiClient, packet.second);
}

void AServer::handleEvent(std::pair<std::shared_ptr<APacket>, asio::ip::udp::endpoint> &packet)
{
    if (!isConnected(packet.second)) return;
    try
    {
        std::shared_ptr<ClientEvent> event = std::dynamic_pointer_cast<ClientEvent>(packet.first);
        if (event->getClientEvent() != ROOM) return;
        std::string eventDesc = event->getDescription();
        size_t pos = eventDesc.find('=');
        if (pos == std::string::npos || this->_eventH.find(eventDesc.substr(0, pos)) == this->_eventH.end())
            std::cerr << "\x1B[31m[AServer Error]\x1B[0m: unknown event : " << eventDesc
                      << std::endl;
        else
            this->_eventH[eventDesc.substr(0, pos)](packet.second, eventDesc);
        auto validation = this->_packetFactory->createEmptyPacket<PacketValidation>();
        validation->setPacketReceiveTimeStamp(packet.first->getPacketTimeStamp());
        validation->setPacketReceiveType(packet.first->getPacketType());
        this->send(validation, packet.second, false);
    }
    catch (std::exception &e)
    {
        std::cerr << "\x1B[31m[AServer Error]\x1B[0m: Error in client event {" << e.what() << "}"
                  << std::endl;
    }
}

bool AServer::isConnected(asio::ip::udp::endpoint &endpoint) const
{
    for (auto &connected : this->_connectedEp)
        if (connected == endpoint) return true;
    return false;
}

void AServer::registerEventHandling(std::string desc, EventFunction handler)
{
    this->_eventH[desc] = handler;
    std::cerr << "\x1B[32m[AServer]\x1B[0m: Event {" << desc << "} registered." << std::endl;
}
}  // namespace dimension