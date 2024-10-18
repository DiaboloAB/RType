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
 * @class MoveEntityPacket
 *
 * @brief Class used to create a Packet that can be serialize and deserialize. This packet hold
 * main information used to move entities in the game.
 */
class MoveEntityPacket : public dimension::APacket
{
   public:
    MoveEntityPacket(uint8_t type) : APacket(type) { this->_packetDataSize =
        sizeof(uint32_t) + sizeof(float) + sizeof(float) + sizeof(float) + sizeof(float); };

    /**
     * @brief Construct MoveEntityPacket object that will be send to server or client.
     *
     * @param entityId : Id of the entity that will be moved.
     * @param posX : X position of the entity.
     * @param posY : Y position of the entity.
     * @param directionX : X direction of the entity
     * @param directionY : Y direction of the entity
     * @return MoveEntityPacket object.
     */
    MoveEntityPacket(uint32_t entityId, float posX, float posY, float directionX, float directionY);

    /**
     * @brief Construct new MoveEntityPacket object with serialized data by deserializing them.
     *
     * @param buffer: Serialized packet data to deserialize.
     * @return MoveEntityPacket object.
     */
    MoveEntityPacket(std::vector<char> &buffer);

    /**
     * @brief Destruct MoveEntityPacket object.
     */
    ~MoveEntityPacket() override;

   public:
    /**
     * @brief Serialize class data to binary to make it sendable by NetworkHandler.
     *
     * @return std::vector<char> that represent serialization of entityId, posX, posY, directionX,
     * directionY to binary.
     */
    std::vector<char> serializeData() const override;

   public:
    uint32_t getEntityId() const;
    float getPosX() const;
    float getPosY() const;
    float getDirectionX() const;
    float getDirectionY() const;

    public:
        void setEntityId(const uint32_t &entityId) {this->_entityId = entityId; };
        void setPosX(const float &posX) { this->_posX = posX; };
        void setPosY(const float &posY) { this->_posX = posY; };
        void setDirectionX(const float &directionX) { this->_directionX = directionX; };
        void setDirectionY(const float &directionY) { this->_directionY = directionY; };

   private:
    uint32_t _entityId;
    float _posX;
    float _posY;
    float _directionX;
    float _directionY;
};
}  // namespace RType::Network
