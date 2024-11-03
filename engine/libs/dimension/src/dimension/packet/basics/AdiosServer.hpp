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
 * @class AdiosServer
 *
 * @brief Class used to create a Packet that can be serialize and deserialize. This packet hold
 * main information used by client to inform server of logout.
 */
class AdiosServer : public APacket
{
   public:
    /**
     * @brief Construct AdiosServer object that will be send to sever.
     *
     * @param type packetType define by class index in packetManager registration.
     * @return AdiosServer object.
     */
    AdiosServer(uint8_t type);

    /**
     * @brief Construct new AdiosServer object with serialized data by deserializing them.
     *
     * @param buffer: Serialized packet data to deserialize.
     * @return AdiosServer object.
     */
    AdiosServer(std::vector<char> &buffer);

    /**
     * @brief Destruct AdiosServer object.
     */
    ~AdiosServer();

   public:
    /**
     * @brief Serialize class data to binary to make it sendable by NetworkHandler.
     *
     * @return empty std::vector<char> because nothing to serialize.
     */
    std::vector<char> serializeData() const override;
};
}  // namespace dimension