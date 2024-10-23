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
AServer::AServer(std::shared_ptr<PacketFactory> &factory, std::string host, unsigned int port)
    : AEndpoint(factory)
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

void AServer::handlePackets()
{
    std::queue<std::pair<std::shared_ptr<APacket>, asio::ip::udp::endpoint>> queueAtT =
        this->_rcvQueue;
    while (!queueAtT.empty())
    {
        auto &packet = queueAtT.front();
    }
}
}  // namespace dimension