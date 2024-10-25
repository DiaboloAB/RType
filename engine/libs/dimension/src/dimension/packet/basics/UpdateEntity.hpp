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
 * @class UpdateEntity
 *
 * @brief Class used to create a Packet that can be serialize and deserialize. This packet hold
 * main information used to update entities in game.
 */
class UpdateEntity : public dimension::APacket
{
   public:
    /**
     * @brief Construct UpdateEntity object that will be send to sever.
     *
     * @param type packet type define by class index in packetManager registration.
     * @return empty UpdateEntity object.
     */
    UpdateEntity(uint8_t type);

    /**
     * @brief Construct new UpdateEntity object with serialized data by deserializing them.
     *
     * @param buffer: Serialized packet data to deserialize.
     * @return UpdateEntity object.
     */
    UpdateEntity(std::vector<char> &buffer);

    /**
     * @brief Destruct UpdateEntity object.
     */
    ~UpdateEntity() override;

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
}  // namespace dimension
