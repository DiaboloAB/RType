/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "MoveEntityPacket.hpp"

namespace RType::Network
{

MoveEntityPacket::MoveEntityPacket(uint32_t entityId, float posX, float posY, float directionX,
                                   float directionY)
    : APacket(MOVEENTITY),
      _entityId(entityId),
      _posX(posX),
      _posY(posY),
      _directionX(directionX),
      _directionY(directionY)
{
    this->_packetDataSize =
        sizeof(uint32_t) + sizeof(float) + sizeof(float) + sizeof(float) + sizeof(float);
}

MoveEntityPacket::MoveEntityPacket(std::vector<char> &buffer) : APacket(buffer)
{
    char *data = buffer.data();
    data += this->getHeaderSize();

    std::memcpy(&this->_entityId, data, sizeof(uint32_t));
    data += sizeof(uint32_t);
    std::memcpy(&this->_posX, data, sizeof(float));
    data += sizeof(float);
    std::memcpy(&this->_posY, data, sizeof(float));
    data += sizeof(float);
    std::memcpy(&this->_directionX, data, sizeof(float));
    data += sizeof(float);
    std::memcpy(&this->_directionY, data, sizeof(float));
}

MoveEntityPacket::~MoveEntityPacket() {}

std::vector<char> MoveEntityPacket::serializeData() const
{
    std::vector<char> buffer;
    buffer.resize(sizeof(uint32_t) + sizeof(float) + sizeof(float) + sizeof(float) + sizeof(float));
    char *data = buffer.data();

    std::memcpy(data, &this->_entityId, sizeof(uint32_t));
    data += sizeof(uint32_t);
    std::memcpy(data, &this->_posX, sizeof(float));
    data += sizeof(float);
    std::memcpy(data, &this->_posY, sizeof(float));
    data += sizeof(float);
    std::memcpy(data, &this->_directionX, sizeof(float));
    data += sizeof(float);
    std::memcpy(data, &this->_directionY, sizeof(float));
    return buffer;
}

uint32_t MoveEntityPacket::getEntityId() const { return this->_entityId; }

float MoveEntityPacket::getPosX() const { return this->_posX; }

float MoveEntityPacket::getPosY() const { return this->_posY; }

float MoveEntityPacket::getDirectionX() const { return this->_directionX; }

float MoveEntityPacket::getDirectionY() const { return this->_directionY; }

}  // namespace RType::Network
