/**********************************************************************************
 *  Project: Dimension Network
 *  Description: Networking Game Library
 *  Author: Morgan LARGEOT, Maxence LARGEOT
 *  Create Time: 2024-10-17
 *  Location: Rennes
 **********************************************************************************/

#include "Client.hpp"

namespace dimension
{
Client::Client(const std::shared_ptr<PacketFactory> &factory) : AEndpoint(factory) {}

Client::~Client()
{
    if (this->_io_context) this->_io_context->stop();
    if (this->_recvThread) this->_recvThread->join();
}

void Client::connectServer(std::string host, unsigned int port)
{
    if (this->_io_context != nullptr) return;
    try
    {
        this->_io_context = std::make_shared<asio::io_context>();
        asio::ip::udp::endpoint endpoint(asio::ip::udp::v4(), 0);
        this->_socket = std::make_shared<asio::ip::udp::socket>(*this->_io_context, endpoint);
        asio::ip::udp::resolver resolver(*this->_io_context);
        asio::ip::udp::resolver::results_type endpoints =
            resolver.resolve(asio::ip::udp::v4(), host, std::to_string(port));
        this->_serverEndpoint = std::make_shared<asio::ip::udp::endpoint>(*endpoints.begin());
        this->_directionEndpoint = _serverEndpoint;
        this->receive();
        this->_recvThread =
            std::make_shared<std::thread>(std::thread([this] { this->_io_context->run(); }));
        auto hiServer = this->_packetFactory->createEmptyPacket<HiServer>();
        this->send(hiServer, *this->_serverEndpoint, false);
        LOG("Client", "Connection to server established.");
    }
    catch (std::exception &e)
    {
        ERR_LOG("Client", e.what());
    }
}

std::shared_ptr<asio::ip::udp::endpoint> Client::getDirectionEndpoint() const
{
    return this->_directionEndpoint;
}

std::chrono::steady_clock::time_point Client::getLastPing() const
{
    return this->_lastPing;
}

void Client::setDirectionEndpoint(std::shared_ptr<asio::ip::udp::endpoint> newDirectionEndpoint)
{
    this->_directionEndpoint = newDirectionEndpoint;
}

void Client::setLastPing(std::chrono::steady_clock::time_point newLastPing)
{
    this->_lastPing = newLastPing;
}

void Client::connectDirectionEndpoint(std::string host, unsigned int port)
{
    asio::ip::udp::resolver resolver(*this->_io_context);
    asio::ip::udp::resolver::results_type endpoints =
            resolver.resolve(asio::ip::udp::v4(), host, std::to_string(port));
    this->_directionEndpoint = std::make_shared<asio::ip::udp::endpoint>(*endpoints.begin());
}
}  // namespace dimension
