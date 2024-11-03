/**********************************************************************************
 *  Project: Dimension Network
 *  Description: Networking Game Library
 *  Author: Morgan LARGEOT, Maxence LARGEOT
 *  Create Time: 2024-10-20
 *  Location: Rennes
 **********************************************************************************/

#include "HiServer.hpp"

namespace dimension
{
HiServer::HiServer(uint8_t type) : APacket(type) { this->_packetDataSize = 0; }

HiServer::HiServer(std::vector<char> &buffer) : APacket(buffer) {}

HiServer::~HiServer(){};

std::vector<char> HiServer::serializeData() const
{
    std::vector<char> buffer;
    return buffer;
}
}  // namespace dimension
