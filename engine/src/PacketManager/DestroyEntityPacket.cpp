/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "DestroyEntityPacket.hpp"

namespace RType::Network
{
DestroyEntityPacket::DestroyEntityPacket(uint32_t entityId)
    : APacket(DESTROYENTITY), _entityId(entityId)
{
    this->_packetDataSize = sizeof(uint32_t);
}

DestroyEntityPacket::DestroyEntityPacket(std::vector<char> &buffer) : APacket(buffer)
{
    char *data = buffer.data();
    data += this->getHeaderSize();

    std::memcpy(&this->_entityId, data, sizeof(uint32_t));
}

DestroyEntityPacket::~DestroyEntityPacket(){};

std::vector<char> DestroyEntityPacket::serializeData() const
{
    std::vector<char> buffer;
    buffer.resize(sizeof(uint32_t));
    char *data = buffer.data();

    std::memcpy(data, &this->_entityId, sizeof(uint32_t));
    return buffer;
}

uint32_t DestroyEntityPacket::getEntityId() const { return this->getEntityId(); }
}  // namespace RType::Network
