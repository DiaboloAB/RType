/**********************************************************************************
 *  Project: Dimension Network
 *  Description: Networking Game Library
 *  Author: Morgan LARGEOT, Maxence LARGEOT
 *  Create Time: 2024-10-17
 *  Location: Rennes
 **********************************************************************************/

#pragma once

#include "AEndpoint.hpp"

namespace dimension
{
class Client : public AEndpoint
{
   public:
    Client(const std::shared_ptr<PacketFactory> &factory);
    ~Client();

   public:
    /**
     * @brief Establish a connection between the client and the server.
     *
     * @param host Host of the server to connect to.
     * @param port Port of the server to connect to.
     */
    void connectServer(std::string host, unsigned int port);

    public:
       std::queue<std::pair<std::shared_ptr<dimension::APacket>, asio::ip::udp::endpoint>> getRcvQueue();

   public:
    std::shared_ptr<asio::ip::udp::endpoint> _serverEndpoint = nullptr;
};
}  // namespace dimension
