/**********************************************************************************
 *  Project: Dimension Network
 *  Description: Networking Game Library
 *  Author: Morgan LARGEOT, Maxence LARGEOT
 *  Create Time: 2024-10-20
 *  Location: Rennes
 **********************************************************************************/

#include "Ping.hpp"

namespace dimension
{
Ping::Ping(uint8_t type) : APacket(type) { this->_packetDataSize = 0; }

Ping::Ping(std::vector<char> &buffer) : APacket(buffer) {}

Ping::~Ping(){};

std::vector<char> Ping::serializeData() const
{
    std::vector<char> buffer;
    return buffer;
}
}  // namespace dimension
