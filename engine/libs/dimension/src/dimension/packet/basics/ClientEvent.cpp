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
ClientEvent::ClientEvent(uint8_t type) : APacket(type) { 
    this->_packetDataSize = sizeof(uint8_t) + _description.size();
}

ClientEvent::ClientEvent(std::vector<char> &buffer) : APacket(buffer)
{
    char *data = buffer.data();
    data += this->getHeaderSize();

    std::memcpy(&this->_clientEvent, data, sizeof(uint8_t));
    data += sizeof(uint8_t);
    this->_description = std::string(data, this->getPacketSize() - this->getHeaderSize() - sizeof(uint8_t));
}

ClientEvent::~ClientEvent() {}

std::vector<char> ClientEvent::serializeData() const
{
    std::vector<char> buffer;
    buffer.resize(sizeof(uint8_t) + this->_description.size());
    char *data = buffer.data();

    std::memcpy(data, &this->_clientEvent, sizeof(uint8_t));
    data += sizeof(uint8_t);
    std::memcpy(data, this->_description.c_str(), this->_description.size());
    return buffer;
}

uint8_t ClientEvent::getClientEvent() const { return this->_clientEvent; }

std::string ClientEvent::getDescription() const { return this->_description; }

void ClientEvent::setClientEvent(const uint8_t &event) { this->_clientEvent = event; }

void ClientEvent::setDescription(const std::string &description) {
    this->_description = description;
    this->_packetDataSize = sizeof(uint8_t) + this->_description.size();
}
}  // namespace dimension