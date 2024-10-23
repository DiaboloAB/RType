/**********************************************************************************
 *  Project: Dimension Network
 *  Description: Networking Game Library
 *  Author: Morgan LARGEOT, Maxence LARGEOT
 *  Create Time: 2024-10-17
 *  Location: Rennes
 **********************************************************************************/

#pragma once

#include "AEndpoint.hpp"
#include "APacketFactory.hpp"

#include <list>

namespace dimension
{
class DimensionServer : public AEndpoint {
   public:
      DimensionServer(std::shared_ptr<APacketFactory> &factory, std::string host, unsigned int port);
      ~DimensionServer() = default;
   public:
      void handlePackets();
      virtual void initRoom(bool isPrivate = false) = 0;
   protected:
      std::queue<std::pair<std::shared_ptr<APacket>, asio::ip::udp::endpoint>> _sendingQueue;
};
}  // namespace dimension
