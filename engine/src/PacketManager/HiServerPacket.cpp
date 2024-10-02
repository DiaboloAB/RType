/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "HiServerPacket.hpp"

namespace RType::Network {
    HiServerPacket::HiServerPacket() : APacket(HISERVER) {
        this->_packetDataSize = 0;
    }

    HiServerPacket::HiServerPacket(std::vector<char> &buffer) : APacket(buffer) {}

    HiServerPacket::~HiServerPacket() {};

    std::vector<char> HiServerPacket::serializeData() const {}
}
