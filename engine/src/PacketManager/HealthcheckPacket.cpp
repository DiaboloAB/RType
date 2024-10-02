/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "HealthcheckPacket.hpp"

namespace RType::Network
{
HealthcheckPacket::HealthcheckPacket() : APacket(HEALTHCHECK) { this->_packetDataSize = 0; }

HealthcheckPacket::HealthcheckPacket(std::vector<char> &buffer) : APacket(buffer) {}

HealthcheckPacket::~HealthcheckPacket(){};

std::vector<char> HealthcheckPacket::serializeData() const {
    std::vector<char> buffer;
    return buffer;
}
}  // namespace RType::Network
