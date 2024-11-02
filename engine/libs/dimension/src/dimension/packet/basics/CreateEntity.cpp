/**********************************************************************************
 *  Project: Dimension Network
 *  Description: Networking Game Library
 *  Author: Morgan LARGEOT, Maxence LARGEOT
 *  Create Time: 2024-10-20
 *  Location: Rennes
 **********************************************************************************/

#include "CreateEntity.hpp"

namespace dimension
{

CreateEntity::CreateEntity(uint8_t type) : APacket(type)
{
    this->_packetDataSize =
        sizeof(uint32_t) + (sizeof(float) * 4) + this->_entityToCreate.size();
}

CreateEntity::CreateEntity(std::vector<char> &buffer) : APacket(buffer)
{
    char *data = buffer.data();
    data += this->getHeaderSize();

    std::memcpy(&this->_networkId, data, sizeof(uint32_t));
    data += sizeof(uint32_t);
    std::memcpy(&this->_posX, data, sizeof(float));
    data += sizeof(float);
    std::memcpy(&this->_posY, data, sizeof(float));
    data += sizeof(float);
    std::memcpy(&this->_scaleX, data, sizeof(float));
    data += sizeof(float);
    std::memcpy(&this->_scaleY, data, sizeof(float));
    data += sizeof(float);
    this->_entityToCreate = std::string(data, this->getPacketSize() - this->getHeaderSize() -
                                                  sizeof(uint32_t) - sizeof(float) - sizeof(float));
}

CreateEntity::~CreateEntity() {}

std::vector<char> CreateEntity::serializeData() const
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
    std::memcpy(data, &this->_scaleX, sizeof(float));
    data += sizeof(float);
    std::memcpy(data, &this->_scaleY, sizeof(float));
    data += sizeof(float);
    std::memcpy(data, this->_entityToCreate.c_str(), this->_entityToCreate.size());
    return buffer;
}

uint32_t CreateEntity::getNetworkId() const { return this->_networkId; }

float CreateEntity::getPosX() const { return this->_posX; }

float CreateEntity::getPosY() const { return this->_posY; }

float CreateEntity::getScaleX() const { return this->_scaleX; }

float CreateEntity::getScaleY() const { return this->_scaleY; }

std::string CreateEntity::getEntityToCreate() const { return this->_entityToCreate; }

void CreateEntity::setNetworkId(const uint32_t &networkId) { this->_networkId = networkId; }

void CreateEntity::setPosX(const float &posX) { this->_posX = posX; }

void CreateEntity::setPosY(const float &posY) { this->_posY = posY; }

void CreateEntity::setScaleX(const float &scaleX) { this->_scaleX = scaleX; }

void CreateEntity::setScaleY(const float &scaleY) { this->_scaleY = scaleY; }

void CreateEntity::setEntityToCreate(const std::string &entityToCreate)
{
    this->_entityToCreate = entityToCreate;
    this->_packetDataSize =
        sizeof(uint32_t) + (sizeof(float) * 4) + this->_entityToCreate.size();
}
}  // namespace dimension
