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
    : AEndpoint(factory), _host(host), _port(port)
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
        LOG("AServer", "Server setup.");
    }
    catch (std::exception &e)
    {
        ERR_LOG("AServer", e.what());
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

bool AServer::isConnected(asio::ip::udp::endpoint &endpoint) const
{
    for (auto &connected : this->_connectedEp)
        if (connected == endpoint) return true;
    return false;
}

void AServer::registerEventHandling(std::string desc, EventFunction handler)
{
    this->_eventH[desc] = handler;
    LOG("AServer", "Event {" + desc + "} registered.");
}
}  // namespace dimension