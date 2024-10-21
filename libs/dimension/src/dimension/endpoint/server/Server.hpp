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

namespace dimension
{
class DimensionServer : public AEndpoint {
   public:
      DimensionServer(std::shared_ptr<APacketFactory> &factory, std::string host, unsigned int port);
      ~DimensionServer();

   private:
};
}  // namespace dimension
