/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "HiServerPacket.hpp"

namespace RType::Network {
    HiServerPacket::HiServerPacket(float runtimeVersion) : APacket(HISERVER), _runtimeVersion(runtimeVersion) {
        this->_packetDataSize = sizeof(float);
    }

    HiServerPacket::HiServerPacket(std::vector<char> &buffer) : APacket(buffer) {
        char *data = buffer.data();
        data += this->getHeaderSize();

        std::memcpy(&this->_runtimeVersion, data, sizeof(float));
    }

    HiServerPacket::~HiServerPacket() {};

    std::vector<char> HiServerPacket::serializeData() const {
        std::vector<char> buffer;
        buffer.resize(sizeof(float));
        char *data = buffer.data();

        std::memcpy(data, &this->_runtimeVersion, sizeof(float));
        return buffer;
    }
}
