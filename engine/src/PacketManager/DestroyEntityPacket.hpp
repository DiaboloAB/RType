/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#pragma once

#include "APacket.hpp"

namespace RType::Network
{

/**
 * @class DestroyEntityPacket
 *
 * @brief Class used to create a Packet that can be serialize and deserialize. This packet hold
 * main information used to destroy entities.
 */
class DestroyEntityPacket : public APacket
{
   public:
    /**
     * @brief Construct DestroyEntityPacket object that will be send to server or client.
     *
     * @param entityId : Id of the entity that will be destroyed.
     * @return DestroyEntityPacket object.
     */
    DestroyEntityPacket(uint32_t entityId);

    /**
     * @brief Construct new DestroyEntityPacket object with serialized data by deserializing them.
     *
     * @param buffer: Serialized packet data to deserialize.
     * @return DestroyEntityPacket object.
     */
    DestroyEntityPacket(std::vector<char> &buffer);

    /**
     * @brief Destruct DestroyEntityPacket object.
     */
    ~DestroyEntityPacket() override;

    public:
        uint32_t getEntityId() const;

   public:
    /**
     * @brief Serialize class data to binary to make it sendable by NetworkHandler.
     *
     * @return std::vector<char> that represent serialization of entityId to binary.
     */
    std::vector<char> serializeData() const override;

   private:
    uint32_t _entityId;
};
}  // namespace RType::Network
