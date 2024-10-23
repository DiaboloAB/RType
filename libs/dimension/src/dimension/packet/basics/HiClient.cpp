/**********************************************************************************
 *  Project: Dimension Network
 *  Description: Networking Game Library
 *  Author: Morgan LARGEOT, Maxence LARGEOT
 *  Create Time: 2024-10-20
 *  Location: Rennes
 **********************************************************************************/

#include "HiClient.hpp"

namespace dimension
{
HiClient::HiClient(uint8_t type) : APacket(type) { this->_packetDataSize = 0; }

HiClient::HiClient(std::vector<char> &buffer) : APacket(buffer) {}

HiClient::~HiClient(){};

std::vector<char> HiClient::serializeData() const
{
    std::vector<char> buffer;
    return buffer;
}

}  // namespace dimension
