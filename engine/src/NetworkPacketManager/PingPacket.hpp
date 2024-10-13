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
 * @class PingPacket
 *
 * @brief Class used to create a Packet that can be serialize and deserialize. This packet hold
 * main information used to verify if client or server is still alive.
 */
class PingPacket : public APacket
{
   public:
    /**
     * @brief Construct PingPacket object that will be send to server or client.
     *
     * @return PingPacket object.
     */
    PingPacket();

    /**
     * @brief Construct new PingPacket object with serialized data by deserializing them.
     *
     * @param buffer: Serialized packet data to deserialize.
     * @return PingPacket object.
     */
    PingPacket(std::vector<char> &buffer);

    /**
     * @brief Destruct PingPacket object.
     */
    ~PingPacket();

   public:
    /**
     * @brief Serialize class data to binary to make it sendable by NetworkHandler.
     *
     * @return empty std::vector<char> because nothing to serialize.
     */
    std::vector<char> serializeData() const override;
};
}  // namespace RType::Network