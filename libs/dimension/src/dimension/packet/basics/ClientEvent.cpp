/**********************************************************************************
 *  Project: Dimension Network
 *  Description: Networking Game Library
 *  Author: Morgan LARGEOT, Maxence LARGEOT
 *  Create Time: 2024-10-20
 *  Location: Rennes
 **********************************************************************************/

#include "ClientEvent.hpp"

namespace dimension
{
ClientEvent::ClientEvent(uint8_t type) : APacket(type) { this->_packetDataSize = sizeof(uint8_t); }

ClientEvent::ClientEvent(std::vector<char> &buffer) : APacket(buffer)
{
    char *data = buffer.data();
    data += this->getHeaderSize();

    std::memcpy(&this->_clientEvent, data, sizeof(uint8_t));
}

ClientEvent::~ClientEvent() {}

std::vector<char> ClientEvent::serializeData() const
{
    std::vector<char> buffer;
    buffer.resize(sizeof(uint8_t));
    char *data = buffer.data();

    std::memcpy(data, &this->_clientEvent, sizeof(uint8_t));
    return buffer;
}

uint8_t ClientEvent::getClientEvent() const { return this->_clientEvent; }

void ClientEvent::setClientEvent(const uint8_t &event) { this->_clientEvent = event; }
}  // namespace dimension