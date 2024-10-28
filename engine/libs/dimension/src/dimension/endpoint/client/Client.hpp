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
    std::shared_ptr<asio::ip::udp::endpoint> getDirectionEndpoint() const;
    std::chrono::steady_clock::time_point getLastPing() const;

   public:
    void setDirectionEndpoint(std::shared_ptr<asio::ip::udp::endpoint> newDirectionEndpoint);
    void setLastPing(std::chrono::steady_clock::time_point newLastPing);

   public:
    /**
     * @brief change direction endpoint of the client based on new ip/port.
     *
     * @param host: Host of the instance.
     * @param port: Port of the instance.
     */
    void connectDirectionEndpoint(std::string host, unsigned int port);

   public:
    std::chrono::steady_clock::time_point _lastPing;
    std::shared_ptr<asio::ip::udp::endpoint> _directionEndpoint = nullptr;
    std::shared_ptr<asio::ip::udp::endpoint> _serverEndpoint = nullptr;
};
}  // namespace dimension
