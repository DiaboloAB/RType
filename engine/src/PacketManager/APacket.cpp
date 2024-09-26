/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "APacket.hpp"

namespace RType::Network {

    std::vector<char> APacket::serialize() const {
        std::vector<char> packet = this->serializeHeader();
        std::vector<char> data = this->serializeData();

        packet.insert(packet.end(), data.begin(), data.end());
        return packet;
    }

    std::vector<char> APacket::serializeHeader() const {
        std::vector<char> buffer;
        buffer.resize(sizeof(uint32_t) + sizeof(uint8_t) + sizeof(uint64_t) + sizeof(uint16_t));

        char *data = buffer.data();
        uint32_t sizePacket = sizeof(uint32_t) + sizeof(uint8_t) + sizeof(uint64_t) + sizeof(uint16_t) + this->_packetDataSize;
        std::memcpy(data, &sizePacket, sizeof(uint32_t));
        data += sizeof(uint32_t);
        std::memcpy(data, &this->_packetType, sizeof(uint8_t));
        data += sizeof(uint8_t);
        std::memcpy(data, &this->_packetTimeStamp, sizeof(uint64_t));
        data += sizeof(uint64_t);
        std::memcpy(data, &this->_packetDataSize, sizeof(uint16_t));

        return buffer;
    }
}