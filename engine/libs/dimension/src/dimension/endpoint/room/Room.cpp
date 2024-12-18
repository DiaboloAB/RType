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

Room::~Room()
{
    if (this->_io_context) this->_io_context->stop();
    while (this->_recvThread && !this->_recvThread->joinable())
        ;
    this->_recvThread->join();
}

void Room::addSenderToRoom(asio::ip::udp::endpoint &sender, uint32_t id)
{
    this->_connectedEp.push_back(std::make_pair(sender, std::chrono::steady_clock::now()));
    this->_connectedId[sender] = id;
}

bool Room::isConnected(asio::ip::udp::endpoint &endpoint) const
{
    for (auto &endp : this->_connectedEp)
        if (endp.first == endpoint) return true;
    return false;
}

void Room::sendPing()
{
    auto pingPacket = this->_packetFactory->createEmptyPacket<dimension::Ping>();
    for (auto &endp : this->_connectedEp) this->send(pingPacket, endp.first, false);
    this->_lastPing = std::chrono::steady_clock::now();
}

void Room::resetPing(asio::ip::udp::endpoint &sender)
{
    for (auto &endp : this->_connectedEp)
    {
        if (endp.first == sender)
        {
            endp.second = std::chrono::steady_clock::now();
            return;
        }
    }
}

std::string Room::getHost() const { return this->_host; }

unsigned int Room::getPort() const { return this->_port; }

std::string Room::getCode() const { return this->_code; }

std::list<std::pair<asio::ip::udp::endpoint, std::chrono::steady_clock::time_point>>
Room::getConnectedEp() const
{
    return this->_connectedEp;
}

std::chrono::steady_clock::time_point Room::getLastPing() { return this->_lastPing; }

std::queue<std::pair<std::shared_ptr<APacket>, asio::ip::udp::endpoint>> Room::getRecvQueue()
{
    return this->_rcvQueue;
};

uint32_t Room::getIdFromSender(asio::ip::udp::endpoint &sender)
{
    if (this->_connectedId.find(sender) != this->_connectedId.end())
        return this->_connectedId.at(sender);
    return 5001;
}

std::unordered_map<asio::ip::udp::endpoint, uint32_t> Room::getIdMap()
{
    return this->_connectedId;
};

void Room::sendToAll(const std::shared_ptr<APacket> &packet, bool isNew)
{
    for (auto &endp : this->_connectedEp)
        this->send(packet, endp.first, isNew);
}

uint64_t Room::getLatencyFromSender(asio::ip::udp::endpoint &sender)
{
    if (this->_connectedLatency.find(sender) == this->_connectedLatency.end()) return 0;
    return this->_connectedLatency.at(sender);
}

void Room::setSenderLatency(asio::ip::udp::endpoint &sender, uint64_t lastPing)
{
    uint64_t currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(
                        std::chrono::system_clock::now().time_since_epoch()).count();
    this->_connectedLatency[sender] = currentTime - lastPing;
    LOG("Room", "Latency client : " + std::to_string(currentTime - lastPing) + "ms.");
}
}  // namespace dimension