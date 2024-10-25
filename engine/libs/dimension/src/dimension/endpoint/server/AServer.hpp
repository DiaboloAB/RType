/**********************************************************************************
 *  Project: Dimension Network
 *  Description: Networking Game Library
 *  Author: Morgan LARGEOT, Maxence LARGEOT
 *  Create Time: 2024-10-17
 *  Location: Rennes
 **********************************************************************************/

#pragma once

#include <list>
#include <memory>
#include <random>

#include "AEndpoint.hpp"
#include "PacketFactory.hpp"
#include "ClientEventType.hpp"

namespace dimension
{
struct RoomState
{
    unsigned int _port;
    int _nbConnected = 0;
    std::list<asio::ip::udp::endpoint> _endpoints;
    bool _inGame = false;
    std::shared_ptr<std::thread> _roomThread = nullptr;
};

class AServer : public AEndpoint
{
   public:
    AServer(const std::shared_ptr<PacketFactory> &factory, std::string host, unsigned int port);
    ~AServer() = default;

   public:
    void run();
    void initRoom(asio::ip::udp::endpoint &sender, bool isPrivate = false);
    // void joinRoom(std::string roomCode, asio::ip::udp::endpoint &sender);
    // void endRoom(asio::ip::udp::endpoint &sender);
    virtual void startRoom(std::string roomCode) = 0;

   protected:
    bool isConnected(asio::ip::udp::endpoint &endpoint) const;

    private:
        void initServer(std::string host, unsigned int port);

   private:
    unsigned int getAvaiblePort() const;
    std::string generateRoomCode() const;
    void handleEvent(std::pair<std::shared_ptr<APacket>, asio::ip::udp::endpoint> &packet);
    void handleHiServer(std::pair<std::shared_ptr<APacket>, asio::ip::udp::endpoint> &packet);

   protected:
    std::unordered_map<std::string, RoomState> _rooms;
    std::unordered_map<std::string, RoomState> _privateRooms;
    std::list<asio::ip::udp::endpoint> _connectedEp;
    std::unordered_map<uint8_t, std::function<
        void(std::pair<std::shared_ptr<APacket>, asio::ip::udp::endpoint> &)>> _packetH;
    std::unordered_map<std::string, std::function<void()>> _eventH;
};
}  // namespace dimension
