/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "ClientEventPacket.hpp"

namespace RType::Network {
    ClientEventPacket::ClientEventPacket() : APacket(CLIENTEVENT) {
        this->_packetDataSize = 0;
    };

    ClientEventPacket::ClientEventPacket(std::vector<char> &buffer) : APacket(buffer) {}

    ClientEventPacket::~ClientEventPacket() {}

    std::vector<char> ClientEventPacket::serializeData() const {
        std::vector<char> buffer;
        return buffer;
    }
}