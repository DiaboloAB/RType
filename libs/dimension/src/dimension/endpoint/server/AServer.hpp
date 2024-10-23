/**********************************************************************************
 *  Project: Dimension Network
 *  Description: Networking Game Library
 *  Author: Morgan LARGEOT, Maxence LARGEOT
 *  Create Time: 2024-10-17
 *  Location: Rennes
 **********************************************************************************/

#pragma once

#include <list>

#include "AEndpoint.hpp"
#include "PacketFactory.hpp"

namespace dimension
{
class AServer : public AEndpoint
{
   public:
    AServer(std::shared_ptr<PacketFactory> &factory, std::string host, unsigned int port);
    ~AServer() = default;

   public:
    void handlePackets();
    virtual void initRoom(bool isPrivate = false) = 0;

   protected:
    std::queue<std::pair<std::shared_ptr<APacket>, asio::ip::udp::endpoint>> _sendingQueue;
};
}  // namespace dimension
