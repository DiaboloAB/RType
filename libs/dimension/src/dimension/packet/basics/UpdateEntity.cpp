/**********************************************************************************
 *  Project: Dimension Network
 *  Description: Networking Game Library
 *  Author: Morgan LARGEOT, Maxence LARGEOT
 *  Create Time: 2024-10-20
 *  Location: Rennes
 **********************************************************************************/

#include "UpdateEntity.hpp"

namespace dimension
{
UpdateEntity::UpdateEntity(uint8_t type) : APacket(type)
{
    this->_packetDataSize = sizeof(uint32_t) + sizeof(uint32_t);
}

UpdateEntity::UpdateEntity(std::vector<char> &buffer) : APacket(buffer)
{
    char *data = buffer.data();
    data += this->getHeaderSize();

    std::memcpy(&this->_networkId, data, sizeof(uint32_t));
    data += sizeof(uint32_t);
    std::memcpy(&this->_score, data, sizeof(uint32_t));
}

UpdateEntity::~UpdateEntity(){};

std::vector<char> UpdateEntity::serializeData() const
{
    std::vector<char> buffer;
    buffer.resize(sizeof(uint32_t) + sizeof(uint32_t));
    char *data = buffer.data();

    std::memcpy(data, &this->_networkId, sizeof(uint32_t));
    data += sizeof(uint32_t);
    std::memcpy(data, &this->_score, sizeof(uint32_t));
    return buffer;
}

uint32_t UpdateEntity::getNetworkId() const { return this->_networkId; }

uint32_t UpdateEntity::getScore() const { return this->_score; }

void UpdateEntity::setNetworkId(const uint32_t &networkId) { this->_networkId = networkId; }

void UpdateEntity::setScore(const uint32_t &score) { this->_score = score; }

}  // namespace dimension
