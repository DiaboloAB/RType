/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "MoveEntityPacket.hpp"

namespace RType::Network
{

MoveEntityPacket::MoveEntityPacket(uint8_t type) : APacket(type) 
{ 
    this->_packetDataSize = sizeof(uint32_t) + sizeof(float) + sizeof(float) + sizeof(float) + sizeof(float);
}

MoveEntityPacket::MoveEntityPacket(std::vector<char> &buffer) : APacket(buffer)
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

MoveEntityPacket::~MoveEntityPacket() {}

std::vector<char> MoveEntityPacket::serializeData() const
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

uint32_t MoveEntityPacket::getNetworkId() const { return this->_networkId; }

float MoveEntityPacket::getPosX() const { return this->_posX; }

float MoveEntityPacket::getPosY() const { return this->_posY; }

float MoveEntityPacket::getDirectionX() const { return this->_directionX; }

float MoveEntityPacket::getDirectionY() const { return this->_directionY; }

void MoveEntityPacket::setNetworkId(const uint32_t &networkId) {this->_networkId = networkId; }

void MoveEntityPacket::setPosX(const float &posX) { this->_posX = posX; }

void MoveEntityPacket::setPosY(const float &posY) { this->_posX = posY; }

void MoveEntityPacket::setDirectionX(const float &directionX) { this->_directionX = directionX; }

void MoveEntityPacket::setDirectionY(const float &directionY) { this->_directionY = directionY; }

}  // namespace RType::Network
