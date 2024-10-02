/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "PacketValidationPacket.hpp"

namespace RType::Network
{
PacketValidationPacket::PacketValidationPacket(PacketType packetType, uint64_t packetTimeStamp)
    : APacket(PACKETVALIDATION), _packetType(packetType), _packetTimeStamp(packetTimeStamp)
{
    this->_packetDataSize = sizeof(PacketType) + sizeof(uint64_t);
}

PacketValidationPacket::PacketValidationPacket(std::vector<char> &buffer) : APacket(buffer)
{
    char *data = buffer.data();
    data += this->getHeaderSize();

    std::memcpy(&this->_packetType, data, sizeof(PacketType));
    data += sizeof(PacketType);
    std::memcpy(&this->_packetTimeStamp, data, sizeof(uint64_t));
}

PacketValidationPacket::~PacketValidationPacket(){};

std::vector<char> PacketValidationPacket::serializeData() const
{
    std::vector<char> buffer;
    buffer.resize(sizeof(PacketType) + sizeof(uint64_t));
    char *data = buffer.data();

    std::memcpy(data, &this->_packetType, sizeof(PacketType));
    data += sizeof(PacketType);
    std::memcpy(data, &this->_packetTimeStamp, sizeof(uint64_t));
    return buffer;
}
}  // namespace RType::Network
