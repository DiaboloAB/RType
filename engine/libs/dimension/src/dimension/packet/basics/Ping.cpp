/**********************************************************************************
 *  Project: Dimension Network
 *  Description: Networking Game Library
 *  Author: Morgan LARGEOT, Maxence LARGEOT
 *  Create Time: 2024-10-20
 *  Location: Rennes
 **********************************************************************************/

#include "Ping.hpp"

namespace dimension
{
Ping::Ping(uint8_t type) : APacket(type) { this->_packetDataSize = sizeof(uint64_t); }

Ping::Ping(std::vector<char> &buffer) : APacket(buffer) 
{
    char *data = buffer.data();
    data += this->getHeaderSize();

    std::memcpy(&this->_recepTs, data, sizeof(uint64_t));
}

Ping::~Ping(){};

std::vector<char> Ping::serializeData() const
{
    std::vector<char> buffer;
    buffer.resize(sizeof(uint64_t));
    char *data = buffer.data();

    std::memcpy(data, &this->_recepTs, sizeof(uint64_t));
    return buffer;
}

uint64_t Ping::getRecepTs() const { return this->_recepTs; }

void Ping::setRecepTs(const uint64_t &ts) { this->_recepTs = ts; }
}  // namespace dimension
