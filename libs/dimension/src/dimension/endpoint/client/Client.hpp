/**********************************************************************************
 *  Project: Dimension Network
 *  Description: Networking Game Library
 *  Author: Morgan LARGEOT, Maxence LARGEOT
 *  Create Time: 2024-10-17
 *  Location: Rennes
 **********************************************************************************/

#pragma once

#include "endpoint/AEndpoint.hpp"

namespace dimension
{
class DimensionClient : public AEndpoint
{
   public:
      DimensionClient(std::shared_ptr<APacketFactory> &factory);
      ~DimensionClient();
   public:
      void connectServer(std::string host, unsigned int port);
   protected:
      void handleDataReceived(std::array<char, 1024> &buffer,
                asio::ip::udp::endpoint &endpoint, std::size_t &bytesRcv) override;
   private:
      std::shared_ptr<asio::ip::udp::endpoint> _serverEndpoint = nullptr;
};
}  // namespace dimension
