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
#include "ClientEventType.hpp"
#include "PacketFactory.hpp"

namespace dimension
{
class AServer : public AEndpoint
{
   public:
    AServer(const std::shared_ptr<PacketFactory> &factory, std::string host, unsigned int port);
    ~AServer() = default;

   public:
    void run();

   private:
    void initServer(std::string host, unsigned int port);

   private:
    void handleEvent(std::pair<std::shared_ptr<APacket>, asio::ip::udp::endpoint> &packet);
    void handleHiServer(std::pair<std::shared_ptr<APacket>, asio::ip::udp::endpoint> &packet);

   protected:
    using EventFunction = std::function<void(asio::ip::udp::endpoint &, std::string &)>;
    using PacketHandler =
        std::function<void(std::pair<std::shared_ptr<APacket>, asio::ip::udp::endpoint> &)>;

   protected:
    void registerEventHandling(std::string desc, EventFunction handler);
    bool isConnected(asio::ip::udp::endpoint &endpoint) const;

   protected:
    std::list<asio::ip::udp::endpoint> _connectedEp;
    std::unordered_map<uint8_t, PacketHandler> _packetH;
    std::unordered_map<std::string, EventFunction> _eventH;
};
}  // namespace dimension
