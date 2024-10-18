/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "CreateEntityPacket.hpp"

namespace RType::Network
{

CreateEntityPacket::CreateEntityPacket(uint8_t type) : APacket(type) 
{
    this->_packetDataSize = sizeof(uint32_t) + sizeof(float) + sizeof(float) + this->_entityToCreate.size();
}

CreateEntityPacket::CreateEntityPacket(std::vector<char> &buffer) : APacket(buffer)
{
    char *data = buffer.data();
    data += this->getHeaderSize();

    std::memcpy(&this->_networkId, data, sizeof(uint32_t));
    data += sizeof(uint32_t);
    std::memcpy(&this->_posX, data, sizeof(float));
    data += sizeof(float);
    std::memcpy(&this->_posY, data, sizeof(float));
    data += sizeof(float);
    this->_entityToCreate = std::string(data, this->getPacketSize() - this->getHeaderSize() -
                                                  sizeof(uint32_t) - sizeof(float) - sizeof(float));
}

CreateEntityPacket::~CreateEntityPacket() {}

std::vector<char> CreateEntityPacket::serializeData() const
{
    std::vector<char> buffer;
    buffer.resize(sizeof(uint32_t) + sizeof(float) + sizeof(float) + this->_entityToCreate.size());
    char *data = buffer.data();

    std::memcpy(data, &this->_networkId, sizeof(uint32_t));
    data += sizeof(uint32_t);
    std::memcpy(data, &this->_posX, sizeof(float));
    data += sizeof(float);
    std::memcpy(data, &this->_posY, sizeof(float));
    data += sizeof(float);
    std::memcpy(data, this->_entityToCreate.c_str(), this->_entityToCreate.size());
    return buffer;
}

uint32_t CreateEntityPacket::getNetworkId() const { return this->_networkId; }

float CreateEntityPacket::getPosX() const { return this->_posX; }

float CreateEntityPacket::getPosY() const { return this->_posY; }

std::string CreateEntityPacket::getEntityToCreate() const { return this->_entityToCreate; }

void CreateEntityPacket::setNetworkId(const uint32_t &networkId) { this->_networkId = networkId; }

void CreateEntityPacket::setPosX(const float &posX) { this->_posX = posX; }

void CreateEntityPacket::setPosY(const float &posY) { this->_posX = posY; }

void CreateEntityPacket::setEntityToCreate(const std::string &entityToCreate) {
    this->_entityToCreate = entityToCreate;
    this->_packetDataSize = sizeof(uint32_t) + sizeof(float) + sizeof(float) +
        this->_entityToCreate.size();
}
}  // namespace RType::Network
