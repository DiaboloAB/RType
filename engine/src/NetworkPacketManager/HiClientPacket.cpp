/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "HiClientPacket.hpp"

namespace RType::Network
{
HiClientPacket::HiClientPacket() : APacket(HICLIENT) { this->_packetDataSize = 0; }

HiClientPacket::HiClientPacket(std::vector<char> &buffer) : APacket(buffer) {}

HiClientPacket::~HiClientPacket() {};

std::vector<char> HiClientPacket::serializeData() const
{
    std::vector<char> buffer;
    return buffer;
}

}  // namespace RType::Network
