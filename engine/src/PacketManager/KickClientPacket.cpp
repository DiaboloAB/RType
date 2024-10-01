/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "KickClientPacket.hpp"

namespace RType::Network {
    KickClientPacket::KickClientPacket() : APacket(KICKCLIENT) {
        this->_packetDataSize = 0;
    }

    KickClientPacket::KickClientPacket(std::vector<char> &buffer) : APacket(buffer) {}

    KickClientPacket::~KickClientPacket() {};

    std::vector<char> KickClientPacket::serializeData() const {}
}
