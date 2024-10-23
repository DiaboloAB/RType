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
 * @class DestroyEntity
 *
 * @brief Class used to create a Packet that can be serialize and deserialize. This packet hold
 * main information used to destroy entities.
 */
class DestroyEntity : public APacket
{
   public:
    /**
     * @brief Construct DestroyEntity object that will be send to sever.
     *
     * @param type packet type define by class index in packetManager registration.
     * @return empty DestroyEntity object.
     */
    DestroyEntity(uint8_t type);

    /**
     * @brief Construct new DestroyEntity object with serialized data by deserializing them.
     *
     * @param buffer: Serialized packet data to deserialize.
     * @return DestroyEntity object.
     */
    DestroyEntity(std::vector<char> &buffer);

    /**
     * @brief Destruct DestroyEntity object.
     */
    ~DestroyEntity() override;

   public:
    /**
     * @brief Serialize class data to binary to make it sendable by NetworkHandler.
     *
     * @return std::vector<char> that represent serialization of networkId to binary.
     */
    std::vector<char> serializeData() const override;

   public:
    uint32_t getNetworkId() const;

   public:
    void setNetworkId(const uint32_t &networkId);

   private:
    uint32_t _networkId;
};
}  // namespace dimension
