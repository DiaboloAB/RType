/**********************************************************************************
 *  Project: Dimension Network
 *  Description: Networking Game Library
 *  Author: Morgan LARGEOT, Maxence LARGEOT
 *  Create Time: 2024-10-17
 *  Location: Rennes
 **********************************************************************************/

#pragma once

#include "endpoint/AEndpoint.hpp"
#include "APacketFactory.hpp"
#include "IRoom.hpp"

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
      void sendToRoom(std::pair<std::shared_ptr<APacket>, asio::ip::udp::endpoint> &packet);
   protected:
      std::list<std::shared_ptr<IRoom>> _privateRoom;
      std::list<std::shared_ptr<IRoom>> _matchMakingRoom;
      std::queue<std::pair<std::shared_ptr<APacket>, asio::ip::udp::endpoint>> _sendingQueue;
};
}  // namespace dimension
