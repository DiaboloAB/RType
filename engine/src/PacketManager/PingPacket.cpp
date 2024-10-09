/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "PingPacket.hpp"

namespace RType::Network
{
PingPacket::PingPacket() : APacket(PING) { this->_packetDataSize = 0; }

PingPacket::PingPacket(std::vector<char> &buffer) : APacket(buffer) {}

PingPacket::~PingPacket() {};

std::vector<char> PingPacket::serializeData() const
{
    std::vector<char> buffer;
    return buffer;
}
}  // namespace RType::Network
