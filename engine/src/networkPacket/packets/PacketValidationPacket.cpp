/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "PacketValidationPacket.hpp"

namespace RType::Network
{
PacketValidationPacket::PacketValidationPacket(uint8_t type) : APacket(type) 
{
    this->_packetDataSize = sizeof(uint8_t) + sizeof(uint64_t);
}

PacketValidationPacket::PacketValidationPacket(std::vector<char> &buffer) : APacket(buffer)
{
    char *data = buffer.data();
    data += this->getHeaderSize();

    std::memcpy(&this->_packetReceiveType, data, sizeof(PacketType));
    data += sizeof(PacketType);
    std::memcpy(&this->_packetReceiveTimeStamp, data, sizeof(uint64_t));
}

PacketValidationPacket::~PacketValidationPacket(){};

std::vector<char> PacketValidationPacket::serializeData() const
{
    std::vector<char> buffer;
    buffer.resize(sizeof(PacketType) + sizeof(uint64_t));
    char *data = buffer.data();

    std::memcpy(data, &this->_packetReceiveType, sizeof(PacketType));
    data += sizeof(PacketType);
    std::memcpy(data, &this->_packetReceiveTimeStamp, sizeof(uint64_t));
    return buffer;
}

uint8_t PacketValidationPacket::getPacketReceiveType() const { return this->_packetReceiveType; }

uint64_t PacketValidationPacket::getPacketReceiveTimeStamp() const
{
    return this->_packetReceiveTimeStamp;
}

void PacketValidationPacket::setPacketReceiveType(const uint8_t &receiveType)
{
    this->_packetReceiveType = receiveType;
}

void PacketValidationPacket::setPacketReceiveTimeStamp(const uint64_t &receiveTimeStamp)
{
    this->_packetReceiveTimeStamp = receiveTimeStamp;
}
}  // namespace RType::Network
