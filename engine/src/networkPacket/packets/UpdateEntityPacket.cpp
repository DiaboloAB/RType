/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "UpdateEntityPacket.hpp"

namespace RType::Network
{
UpdateEntityPacket::UpdateEntityPacket(uint8_t type) : APacket(type)
{
    this->_packetDataSize = sizeof(uint32_t) + sizeof(uint32_t);
}

UpdateEntityPacket::UpdateEntityPacket(std::vector<char> &buffer) : APacket(buffer)
{
    char *data = buffer.data();
    data += this->getHeaderSize();

    std::memcpy(&this->_networkId, data, sizeof(uint32_t));
    data += sizeof(uint32_t);
    std::memcpy(&this->_score, data, sizeof(uint32_t));
}

UpdateEntityPacket::~UpdateEntityPacket(){};

std::vector<char> UpdateEntityPacket::serializeData() const
{
    std::vector<char> buffer;
    buffer.resize(sizeof(uint32_t) + sizeof(uint32_t));
    char *data = buffer.data();

    std::memcpy(data, &this->_networkId, sizeof(uint32_t));
    data += sizeof(uint32_t);
    std::memcpy(data, &this->_score, sizeof(uint32_t));
    return buffer;
}

uint32_t UpdateEntityPacket::getNetworkId() const { return this->_networkId; }

uint32_t UpdateEntityPacket::getScore() const { return this->_score; }

void UpdateEntityPacket::setNetworkId(const uint32_t &networkId) { this->_networkId = networkId; }

void UpdateEntityPacket::setScore(const uint32_t &score) { this->_score = score; }

}  // namespace RType::Network
