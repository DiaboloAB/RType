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
 * @class Ping
 *
 * @brief Class used to create a Packet that can be serialize and deserialize. This packet hold
 * main information used to verify if client or server is still alive.
 */
class Ping : public APacket
{
   public:
    /**
     * @brief Construct Ping object that will be send to sever.
     *
     * @param type packet type define by class index in packetManager registration.
     * @return empty Ping object.
     */
    Ping(uint8_t type);

    /**
     * @brief Construct new Ping object with serialized data by deserializing them.
     *
     * @param buffer: Serialized packet data to deserialize.
     * @return Ping object.
     */
    Ping(std::vector<char> &buffer);

    /**
     * @brief Destruct Ping object.
     */
    ~Ping();

   public:
    /**
     * @brief Serialize class data to binary to make it sendable by NetworkHandler.
     *
     * @return empty std::vector<char> because nothing to serialize.
     */
    std::vector<char> serializeData() const override;
};
}  // namespace dimension