/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "ClientEventPacket.hpp"

namespace RType::Network
{
ClientEventPacket::ClientEventPacket(ClientEvent clientEvent)
    : APacket(CLIENTEVENT), _clientEvent(clientEvent)
{
    this->_packetDataSize = sizeof(uint8_t);
};

ClientEventPacket::ClientEventPacket(std::vector<char> &buffer) : APacket(buffer)
{
    char *data = buffer.data();
    data += this->getHeaderSize();

    std::memcpy(&this->_clientEvent, data, sizeof(uint8_t));
}

ClientEventPacket::~ClientEventPacket() {}

std::vector<char> ClientEventPacket::serializeData() const
{
    std::vector<char> buffer;
    buffer.resize(sizeof(uint8_t));
    char *data = buffer.data();

    std::memcpy(data, &this->_clientEvent, sizeof(uint8_t));
    return buffer;
}

ClientEvent ClientEventPacket::getClientEvent() const { return this->_clientEvent; }
}  // namespace RType::Network