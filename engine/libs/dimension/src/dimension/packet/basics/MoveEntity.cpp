/**********************************************************************************
 *  Project: Dimension Network
 *  Description: Networking Game Library
 *  Author: Morgan LARGEOT, Maxence LARGEOT
 *  Create Time: 2024-10-20
 *  Location: Rennes
 **********************************************************************************/

#include "MoveEntity.hpp"

namespace dimension
{

MoveEntity::MoveEntity(uint8_t type) : APacket(type)
{
    this->_packetDataSize =
        sizeof(uint32_t) + sizeof(float) + sizeof(float) + sizeof(float) + sizeof(float);
}

MoveEntity::MoveEntity(std::vector<char> &buffer) : APacket(buffer)
{
    char *data = buffer.data();
    data += this->getHeaderSize();

    std::memcpy(&this->_networkId, data, sizeof(uint32_t));
    data += sizeof(uint32_t);
    std::memcpy(&this->_posX, data, sizeof(float));
    data += sizeof(float);
    std::memcpy(&this->_posY, data, sizeof(float));
    data += sizeof(float);
    std::memcpy(&this->_directionX, data, sizeof(float));
    data += sizeof(float);
    std::memcpy(&this->_directionY, data, sizeof(float));
}

MoveEntity::~MoveEntity() {}

std::vector<char> MoveEntity::serializeData() const
{
    std::vector<char> buffer;
    buffer.resize(sizeof(uint32_t) + sizeof(float) + sizeof(float) + sizeof(float) + sizeof(float));
    char *data = buffer.data();

    std::memcpy(data, &this->_networkId, sizeof(uint32_t));
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

uint32_t MoveEntity::getNetworkId() const { return this->_networkId; }

float MoveEntity::getPosX() const { return this->_posX; }

float MoveEntity::getPosY() const { return this->_posY; }

float MoveEntity::getDirectionX() const { return this->_directionX; }

float MoveEntity::getDirectionY() const { return this->_directionY; }

void MoveEntity::setNetworkId(const uint32_t &networkId) { this->_networkId = networkId; }

void MoveEntity::setPosX(const float &posX) { this->_posX = posX; }

void MoveEntity::setPosY(const float &posY) { this->_posY = posY; }

void MoveEntity::setDirectionX(const float &directionX) { this->_directionX = directionX; }

void MoveEntity::setDirectionY(const float &directionY) { this->_directionY = directionY; }

}  // namespace dimension
