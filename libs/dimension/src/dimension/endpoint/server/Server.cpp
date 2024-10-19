/**********************************************************************************
 *  Project: Dimension Network
 *  Description: Networking Game Library
 *  Author: Morgan LARGEOT, Maxence LARGEOT
 *  Create Time: 2024-10-17
 *  Location: Rennes
  **********************************************************************************/

#include "Server.hpp"

namespace dimension {
DimensionServer::DimensionServer(std::shared_ptr<APacketFactory> &factory, std::string host, unsigned int port)
    : AEndpoint(factory) {}
}