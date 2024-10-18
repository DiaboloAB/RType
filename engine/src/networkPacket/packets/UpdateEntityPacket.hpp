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
 * @class UpdateEntityPacket
 *
 * @brief Class used to create a Packet that can be serialize and deserialize. This packet hold
 * main information used to update entities in game.
 */
class UpdateEntityPacket : public dimension::APacket
{
   public:
    /**
     * @brief Construct UpdateEntityPacket object that will be send to sever.
     *
     * @param type packet type define by class index in packetManager registration.
     * @return empty UpdateEntityPacket object.
     */
    UpdateEntityPacket(uint8_t type);

    /**
     * @brief Construct new UpdateEntityPacket object with serialized data by deserializing them.
     *
     * @param buffer: Serialized packet data to deserialize.
     * @return UpdateEntityPacket object.
     */
    UpdateEntityPacket(std::vector<char> &buffer);

    /**
     * @brief Destruct UpdateEntityPacket object.
     */
    ~UpdateEntityPacket() override;

   public:
    /**
     * @brief Serialize class data to binary to make it sendable by NetworkHandler.
     *
     * @return std::vector<char> that represent serialization of networkId, score to binary.
     */
    std::vector<char> serializeData() const override;

   public:
    uint32_t getNetworkId() const;
    uint32_t getScore() const;

    public:
        void setNetworkId(const uint32_t &networkId);
        void setScore(const uint32_t &score);

   private:
    uint32_t _networkId;
    uint32_t _score;
};
}  // namespace RType::Network
