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
        this->receive();
        this->_recvThread =
            std::make_shared<std::thread>(std::thread([this] { this->_io_context->run(); }));
        auto hiServer = this->_packetFactory->createEmptyPacket<HiServer>();
        this->send(hiServer, *this->_serverEndpoint, false);
        std::cerr << "\x1B[32m[Client]\x1B[0m: Connection to server established." << std::endl;
    }
    catch (std::exception &e)
    {
        std::cerr << "\x1B[31m[Client ERROR]\x1B[0m: " << e.what() << std::endl;
    }
}

std::queue<std::pair<std::shared_ptr<dimension::APacket>, asio::ip::udp::endpoint>> Client::getRcvQueue()
{
    std::lock_guard<std::mutex> lock(this->_queueMutex);
    return this->_rcvQueue; 
}; 
}  // namespace dimension
