/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#pragma once

#include "APacket.hpp"
#include "common/PacketType.hpp"

namespace RType::Network
{

/**
 * @class CreateEntityPacket
 *
 * @brief Class used to create a Packet that can be serialize and deserialize. This packet hold
 * main information used to create new entities.
 */
class CreateEntityPacket : public dimension::APacket
{
   public:
    /**
     * @brief Construct CreateEntityPacket object that will be send to sever.
     *
     * @param type packet type define by class index in packetManager registration.
     * @return empty CreateEntityPacket object.
     */
    CreateEntityPacket(uint8_t type);

    /**
     * @brief Construct new CreateEntityPacket object with serialized data by deserializing them.
     *
     * @param buffer: Serialized packet data to deserialize.
     * @return CreateEntityPacket object.
     */
    CreateEntityPacket(std::vector<char> &buffer);

    /**
     * @brief Destruct CreateEntityPacket object.
     */
    ~CreateEntityPacket() override;

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
}  // namespace RType::Network
