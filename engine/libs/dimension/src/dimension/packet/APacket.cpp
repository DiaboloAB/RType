/**********************************************************************************
 *  Project: Dimension Network
 *  Description: Networking Game Library
 *  Author: Morgan LARGEOT, Maxence LARGEOT
 *  Create Time: 2024-10-17
 *  Location: Rennes
 **********************************************************************************/

#include "APacket.hpp"

namespace dimension
{

APacket::APacket(uint8_t type) : _packetType(type)
{
    this->_packetTimeStamp = std::chrono::duration_cast<std::chrono::seconds>(
                                 std::chrono::system_clock::now().time_since_epoch())
                                 .count();
}

APacket::APacket(std::vector<char> &buffer)
{
    if ((sizeof(uint32_t) + sizeof(uint8_t) + sizeof(uint64_t) + sizeof(uint16_t)) > buffer.size())
        throw new PacketException(
            "PacketException: Unable to deserialize packet. Packet is too small.");
    char *data = buffer.data();

    std::memcpy(&this->_packetSize, data, sizeof(uint32_t));
    data += sizeof(uint32_t);
    std::memcpy(&this->_packetType, data, sizeof(uint8_t));
    data += sizeof(uint8_t);
    std::memcpy(&this->_packetTimeStamp, data, sizeof(uint64_t));
    data += sizeof(uint64_t);
    std::memcpy(&this->_packetDataSize, data, sizeof(uint16_t));
}

std::vector<char> APacket::serialize() const
{
    std::vector<char> packet = this->serializeHeader();
    std::vector<char> data = this->serializeData();

    packet.insert(packet.end(), data.begin(), data.end());
    return packet;
}

std::vector<char> APacket::serializeHeader() const
{
    std::vector<char> buffer;
    buffer.resize(sizeof(uint32_t) + sizeof(uint8_t) + sizeof(uint64_t) + sizeof(uint16_t));

    char *data = buffer.data();
    uint32_t sizePacket = sizeof(uint32_t) + sizeof(uint8_t) + sizeof(uint64_t) + sizeof(uint16_t) +
                          this->_packetDataSize;
    std::memcpy(data, &sizePacket, sizeof(uint32_t));
    data += sizeof(uint32_t);
    std::memcpy(data, &this->_packetType, sizeof(uint8_t));
    data += sizeof(uint8_t);
    std::memcpy(data, &this->_packetTimeStamp, sizeof(uint64_t));
    data += sizeof(uint64_t);
    std::memcpy(data, &this->_packetDataSize, sizeof(uint16_t));

    return buffer;
}

uint32_t APacket::getPacketSize() const { return this->_packetSize; }

uint32_t APacket::getPacketSizeFromBuffer(std::vector<char> &buffer)
{
    if (sizeof(uint32_t) > buffer.size())
        throw new PacketException("PacketException: Impossible to retrieve packet size.");
    uint32_t packetSize;
    std::memcpy(&packetSize, buffer.data(), sizeof(uint32_t));
    return packetSize;
}

uint8_t APacket::getPacketType() const { return this->_packetType; }

uint64_t APacket::getPacketTimeStamp() const { return this->_packetTimeStamp; }

uint8_t APacket::getPacketTypeFromBuffer(std::vector<char> &buffer)
{
    if (sizeof(uint32_t) + sizeof(uint8_t) > buffer.size())
        throw new PacketException("PacketException: Impossible to retrieve packet type.");
    uint8_t packetType;
    char *data = buffer.data() + sizeof(uint32_t);
    std::memcpy(&packetType, data, sizeof(uint8_t));
    return packetType;
}

uint32_t APacket::getHeaderSize() const
{
    return sizeof(uint32_t) + sizeof(uint8_t) + sizeof(uint64_t) + sizeof(uint16_t);
}
}  // namespace dimension
