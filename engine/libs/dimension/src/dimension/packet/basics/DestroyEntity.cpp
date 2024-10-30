/**********************************************************************************
 *  Project: Dimension Network
 *  Description: Networking Game Library
 *  Author: Morgan LARGEOT, Maxence LARGEOT
 *  Create Time: 2024-10-20
 *  Location: Rennes
 **********************************************************************************/

#include "DestroyEntity.hpp"

namespace dimension
{
DestroyEntity::DestroyEntity(uint8_t type) : APacket(type)
{
    this->_packetDataSize = sizeof(uint32_t);
}

DestroyEntity::DestroyEntity(std::vector<char> &buffer) : APacket(buffer)
{
    char *data = buffer.data();
    data += this->getHeaderSize();

    std::memcpy(&this->_networkId, data, sizeof(uint32_t));
}

DestroyEntity::~DestroyEntity() {};

std::vector<char> DestroyEntity::serializeData() const
{
    std::vector<char> buffer;
    buffer.resize(sizeof(uint32_t));
    char *data = buffer.data();

    std::memcpy(data, &this->_networkId, sizeof(uint32_t));
    return buffer;
}

uint32_t DestroyEntity::getNetworkId() const { return this->_networkId; }

void DestroyEntity::setNetworkId(const uint32_t &networkId) { this->_networkId = networkId; }
}  // namespace dimension
