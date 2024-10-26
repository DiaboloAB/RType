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
 * @class MoveEntity
 *
 * @brief Class used to create a Packet that can be serialize and deserialize. This packet hold
 * main information used to move entities in the game.
 */
class MoveEntity : public APacket
{
   public:
    /**
     * @brief Construct MoveEntity object that will be send to sever.
     *
     * @param type packet type define by class index in packetManager registration.
     * @return empty MoveEntity object.
     */
    MoveEntity(uint8_t type);

    /**
     * @brief Construct new MoveEntity object with serialized data by deserializing them.
     *
     * @param buffer: Serialized packet data to deserialize.
     * @return MoveEntity object.
     */
    MoveEntity(std::vector<char> &buffer);

    /**
     * @brief Destruct MoveEntity object.
     */
    ~MoveEntity() override;

   public:
    /**
     * @brief Serialize class data to binary to make it sendable by NetworkHandler.
     *
     * @return std::vector<char> that represent serialization of networkId, posX, posY, directionX,
     * directionY to binary.
     */
    std::vector<char> serializeData() const override;

   public:
    uint32_t getNetworkId() const;
    float getPosX() const;
    float getPosY() const;
    float getDirectionX() const;
    float getDirectionY() const;

   public:
    void setNetworkId(const uint32_t &networkId);
    void setPosX(const float &posX);
    void setPosY(const float &posY);
    void setDirectionX(const float &directionX);
    void setDirectionY(const float &directionY);

   private:
    uint32_t _networkId;
    float _posX;
    float _posY;
    float _directionX;
    float _directionY;
};
}  // namespace dimension
