/**********************************************************************************
 *  Project: Dimension Network
 *  Description: Networking Game Library
 *  Author: Morgan LARGEOT, Maxence LARGEOT
 *  Create Time: 2024-10-20
 *  Location: Rennes
 **********************************************************************************/

#include "PacketValidation.hpp"

namespace dimension
{
PacketValidation::PacketValidation(uint8_t type) : APacket(type)
{
    this->_packetDataSize = sizeof(uint8_t) + sizeof(uint64_t);
}

PacketValidation::PacketValidation(std::vector<char> &buffer) : APacket(buffer)
{
    char *data = buffer.data();
    data += this->getHeaderSize();

    std::memcpy(&this->_packetReceiveType, data, sizeof(uint8_t));
    data += sizeof(uint8_t);
    std::memcpy(&this->_packetReceiveTimeStamp, data, sizeof(uint64_t));
}

PacketValidation::~PacketValidation(){};

std::vector<char> PacketValidation::serializeData() const
{
    std::vector<char> buffer;
    buffer.resize(sizeof(uint8_t) + sizeof(uint64_t));
    char *data = buffer.data();

    std::memcpy(data, &this->_packetReceiveType, sizeof(uint8_t));
    data += sizeof(uint8_t);
    std::memcpy(data, &this->_packetReceiveTimeStamp, sizeof(uint64_t));
    return buffer;
}

uint8_t PacketValidation::getPacketReceiveType() const { return this->_packetReceiveType; }

uint64_t PacketValidation::getPacketReceiveTimeStamp() const
{
    return this->_packetReceiveTimeStamp;
}

void PacketValidation::setPacketReceiveType(const uint8_t &receiveType)
{
    this->_packetReceiveType = receiveType;
}

void PacketValidation::setPacketReceiveTimeStamp(const uint64_t &receiveTimeStamp)
{
    this->_packetReceiveTimeStamp = receiveTimeStamp;
}
}  // namespace dimension
