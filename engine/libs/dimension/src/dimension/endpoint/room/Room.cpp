/**********************************************************************************
 *   Project: Dimension Network
 *   Description: Networking Game Library
 *   Author: Morgan LARGEOT, Maxence LARGEOT
 *   Create Time: 2024-10-27
 *   Location: Rennes
 **********************************************************************************/

#include "Room.hpp"

namespace dimension
{
Room::Room(const std::shared_ptr<PacketFactory> &factory, std::string host, unsigned int port,
           std::string code)
    : AEndpoint(factory), _host(host), _port(port), _code(code)
{
    try
    {
        this->_lastPing = std::chrono::steady_clock::now();
        this->_io_context = std::make_shared<asio::io_context>();
        asio::ip::udp::endpoint endpoint(asio::ip::udp::v4(), port);
        this->_socket = std::make_shared<asio::ip::udp::socket>(*this->_io_context, endpoint);
        this->receive();
        this->_recvThread =
            std::make_shared<std::thread>(std::thread([this] { this->_io_context->run(); }));
        LOG("Room", "Room successfully set.");
    }
    catch (std::exception &e)
    {
        ERR_LOG("Room", e.what());
    }
}

Room::~Room() {}

void Room::pingEndpoints()
{
    std::chrono::steady_clock::time_point actualTime = std::chrono::steady_clock::now();
    if (std::chrono::duration_cast<std::chrono::milliseconds>(actualTime - this->_lastPing)
            .count() >= 500)
    {
        auto ping = this->_packetFactory->createEmptyPacket<Ping>();
        for (auto &endp : this->_connectedEp) this->send(ping, endp.first, false);
        this->_lastPing = std::chrono::steady_clock::now();
    }
}

void Room::addSenderToRoom(asio::ip::udp::endpoint &sender)
{
    this->_connectedEp.push_back(std::make_pair(sender, std::chrono::steady_clock::now()));
}

bool Room::isConnected(asio::ip::udp::endpoint &endpoint) const
{
    for (auto &endp : this->_connectedEp)
        if (endp.first == endpoint) return true;
    return false;
}
}  // namespace dimension