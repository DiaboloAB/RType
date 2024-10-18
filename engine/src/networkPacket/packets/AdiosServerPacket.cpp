/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "AdiosServerPacket.hpp"

namespace RType::Network
{
AdiosServerPacket::AdiosServerPacket(uint8_t type) : APacket(type) { this->_packetDataSize = 0; }

AdiosServerPacket::AdiosServerPacket(std::vector<char> &buffer) : APacket(buffer) {}

AdiosServerPacket::~AdiosServerPacket(){};

std::vector<char> AdiosServerPacket::serializeData() const
{
    std::vector<char> buffer;
    return buffer;
}
}  // namespace RType::Network
