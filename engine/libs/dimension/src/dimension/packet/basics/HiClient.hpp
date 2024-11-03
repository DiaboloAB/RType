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
 * @class HiClient
 *
 * @brief Class used to create a Packet that can be serialize and deserialize. This packet hold
 * main information used to ping server from new client.
 */
class HiClient : public dimension::APacket
{
   public:
    /**
     * @brief Construct HiClient object that will be send to sever.
     *
     * @param type packet type define by class index in packetManager registration.
     * @return empty HiClient object.
     */
    HiClient(uint8_t type);

    /**
     * @brief Construct new HiClient object with serialized data by deserializing them.
     *
     * @param buffer: Serialized packet data to deserialize.
     * @return HiClient object.
     */
    HiClient(std::vector<char> &buffer);

    /**
     * @brief Destruct HiClient object.
     */
    ~HiClient();

   public:
    /**
     * @brief Serialize class data to binary to make it sendable by NetworkHandler.
     *
     * @return empty std::vector<char> because nothing to serialize.
     */
    std::vector<char> serializeData() const override;

   private:
};
}  // namespace dimension