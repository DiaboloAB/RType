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

      /**
       * @brief Establish a connection between the client and the server.
       *
       * @param host Host of the server to connect to.
       * @param port Port of the server to connect to.
       */
      void connectServer(std::string host, unsigned int port);
   private:
      std::shared_ptr<asio::ip::udp::endpoint> _serverEndpoint = nullptr;
};
}  // namespace dimension
