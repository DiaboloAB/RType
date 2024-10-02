/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "HiClientPacket.hpp"

namespace RType::Network
{
HiClientPacket::HiClientPacket(uint32_t entityId) : APacket(HICLIENT), _entityId(entityId)
{
    this->_packetDataSize = sizeof(uint32_t);
}

HiClientPacket::HiClientPacket(std::vector<char> &buffer) : APacket(buffer)
{
    char *data = buffer.data();
    data += this->getHeaderSize();

    std::memcpy(&this->_entityId, data, sizeof(uint32_t));
}

HiClientPacket::~HiClientPacket(){};

std::vector<char> HiClientPacket::serializeData() const
{
    std::vector<char> buffer;
    buffer.resize(sizeof(uint32_t));
    char *data = buffer.data();

    std::memcpy(data, &this->_entityId, sizeof(uint32_t));
    return buffer;
}
}  // namespace RType::Network
