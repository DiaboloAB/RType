/**********************************************************************************
 *   Project: Dimension Network
 *   Description: Networking Game Library
 *   Author: Morgan LARGEOT, Maxence LARGEOT
 *   Create Time: 2024-10-27
 *   Location: Rennes
 **********************************************************************************/

#pragma once

#include <asio.hpp>
#include <chrono>
#include <list>
#include <string>

#include "AEndpoint.hpp"

namespace dimension
{

/**
 * @class Room
 *
 * @brief The Room class implements game logic in an ECS, operating in server mode
 * with authoritative control over game entities.
 */
class Room : public AEndpoint
{
   public:
    /**
     * @brief Constructs a Room for server-mode implementation in the engine.
     *
     * @param factory PacketFactory for creating and handling packets (custom / lib)
     * @param host IP address for the room (e.g., "127.0.0.1")
     * @param port UDP port for room communication
     * @param code Unique game code for client connection management
     */
    Room(const std::shared_ptr<PacketFactory> &factory, std::string host, unsigned int port,
         std::string code);
    ~Room();

   public:
    /**
     * @brief Pings connected endpoints to maintain active connections.
     */
    void pingEndpoints();

   public:
    /**
     * @brief Adds a sender endpoint to connected endpoints for handling non-connection packets.
     *
     * @param sender Endpoint to add to the connected endpoints list.
     */
    void addSenderToRoom(asio::ip::udp::endpoint &sender);

    /**
     * @brief Check if a client is connected to the server.
     *
     * @param endpoint: Endpoint of the client to ckeck.
     * @return True if connected.
     * @return False otherwise.
     */
    bool isConnected(asio::ip::udp::endpoint &endpoint) const;

    /**
     * @brief Send ping packet to all connected clients of the room.
     */
    void sendPing() override;

    /**
     * @brief Reset the last ping value of the sender of the packet ping.
     * 
     * @param sender: Sender of the packet.
     */
    void resetPing(asio::ip::udp::endpoint &sender);

   public:
    std::string getHost() const;
    unsigned int getPort() const;
    std::string getCode() const;
    std::list<std::pair<asio::ip::udp::endpoint, std::chrono::steady_clock::time_point>>
    getConnectedEp() const;
    std::chrono::steady_clock::time_point getLastPing();
    std::queue<std::pair<std::shared_ptr<APacket>, asio::ip::udp::endpoint>> getRecvQueue();

   private:
    std::string _host;
    unsigned int _port;
    std::string _code;
    std::list<std::pair<asio::ip::udp::endpoint, std::chrono::steady_clock::time_point>>
        _connectedEp;
    std::chrono::steady_clock::time_point _lastPing;
};
}  // namespace dimension