/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "UpdateEntityPacket.hpp"

namespace RType::Network
{
UpdateEntityPacket::UpdateEntityPacket(uint32_t entityId, uint32_t score)
    : APacket(UPDATEENTITY), _entityId(entityId), _score(score)
{
    this->_packetDataSize = sizeof(uint32_t) + sizeof(uint32_t);
}

UpdateEntityPacket::UpdateEntityPacket(std::vector<char> &buffer) : APacket(buffer)
{
    char *data = buffer.data();
    data += this->getHeaderSize();

    std::memcpy(&this->_entityId, data, sizeof(uint32_t));
    data += sizeof(uint32_t);
    std::memcpy(&this->_score, data, sizeof(uint32_t));
}

UpdateEntityPacket::~UpdateEntityPacket(){};

std::vector<char> UpdateEntityPacket::serializeData() const
{
    std::vector<char> buffer;
    buffer.resize(sizeof(uint32_t) + sizeof(uint32_t));
    char *data = buffer.data();

    std::memcpy(data, &this->_entityId, sizeof(uint32_t));
    data += sizeof(uint32_t);
    std::memcpy(data, &this->_score, sizeof(uint32_t));
    return buffer;
}
}  // namespace RType::Network
