/**********************************************************************************
 *  Project: Dimension Network
 *  Description: Networking Game Library
 *  Author: Morgan LARGEOT, Maxence LARGEOT
 *  Create Time: 2024-10-20
 *  Location: Rennes
 **********************************************************************************/

#include "AdiosServer.hpp"

namespace dimension
{
AdiosServer::AdiosServer(uint8_t type) : APacket(type) { this->_packetDataSize = 0; }

AdiosServer::AdiosServer(std::vector<char> &buffer) : APacket(buffer) {}

AdiosServer::~AdiosServer(){};

std::vector<char> AdiosServer::serializeData() const
{
    std::vector<char> buffer;
    return buffer;
}
}  // namespace dimension
