/**********************************************************************************
 *  Project: Dimension Network
 *  Description: Networking Game Library
 *  Author: Morgan LARGEOT, Maxence LARGEOT
 *  Create Time: 2024-10-20
 *  Location: Rennes
 **********************************************************************************/

#pragma once

#include "APacket.hpp"

namespace dimension
{

/**
 * @class CreateEntity
 *
 * @brief Class used to create a Packet that can be serialize and deserialize. This packet hold
 * main information used to create new entities.
 */
class CreateEntity : public APacket
{
   public:
    /**
     * @brief Construct CreateEntity object that will be send to sever.
     *
     * @param type packet type define by class index in packetManager registration.
     * @return empty CreateEntity object.
     */
    CreateEntity(uint8_t type);

    /**
     * @brief Construct new CreateEntity object with serialized data by deserializing them.
     *
     * @param buffer: Serialized packet data to deserialize.
     * @return CreateEntity object.
     */
    CreateEntity(std::vector<char> &buffer);

    /**
     * @brief Destruct CreateEntity object.
     */
    ~CreateEntity() override;

   public:
    /**
     * @brief Serialize class data to binary to make it sendable by NetworkHandler.
     *
     * @return std::vector<char> that represent serialization of networkId, posX, posY,
     * entityToCreate to binary.
     */
    std::vector<char> serializeData() const override;

   public:
    uint32_t getNetworkId() const;
    float getPosX() const;
    float getPosY() const;
    std::string getEntityToCreate() const;

   public:
    void setNetworkId(const uint32_t &networkId);
    void setPosX(const float &posX);
    void setPosY(const float &posY);
    void setEntityToCreate(const std::string &entityToCreate);

   private:
    uint32_t _networkId;
    float _posX;
    float _posY;
    std::string _entityToCreate;
};
}  // namespace dimension
