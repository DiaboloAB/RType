/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "CreateEntityPacket.hpp"

namespace RType::Network {
    
    CreateEntityPacket::CreateEntityPacket(uint32_t entityId, float posX, float posY) : APacket(CREATEENTITY),
    _entityId(entityId), _posX(posX), _posY(posY) {
        this->_packetDataSize = sizeof(uint32_t) + sizeof(float) + sizeof(float);
    }

    CreateEntityPacket::~CreateEntityPacket() {}

    std::vector<char> CreateEntityPacket::serializeData() const {
        std::vector<char> buffer;
        buffer.resize(sizeof(uint32_t) + sizeof(float) + sizeof(float));
        char *data = buffer.data();

        std::memcpy(data, &this->_entityId, sizeof(uint32_t));
        data += sizeof(uint32_t);
        std::memcpy(data, &this->_posX, sizeof(float));
        data += sizeof(float);
        std::memcpy(data, &this->_posY, sizeof(float));

        return buffer;
    }
}