/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "KickClientPacket.hpp"

namespace RType::Network
{
KickClientPacket::KickClientPacket(std::string reason) : APacket(KICKCLIENT), _reason(reason)
{
    this->_packetDataSize = this->_reason.size();
}

KickClientPacket::KickClientPacket(std::vector<char> &buffer) : APacket(buffer)
{
    char *data = buffer.data();
    data += this->getHeaderSize();

    this->_reason = std::string(data, this->getPacketSize() - this->getHeaderSize());
}

KickClientPacket::~KickClientPacket() {};

std::vector<char> KickClientPacket::serializeData() const
{
    std::vector<char> buffer;
    buffer.resize(this->_reason.size());
    char *data = buffer.data();

    std::memcpy(data, this->_reason.c_str(), this->_reason.size());
    return buffer;
}

std::string KickClientPacket::getReason() const { return this->_reason; }
}  // namespace RType::Network