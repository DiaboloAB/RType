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
 * @class HealthcheckPacket
 *
 * @brief Class used to create a Packet that can be serialize and deserialize. This packet hold
 * main information used to verify if client or server is still alive.
 */
class HealthcheckPacket : public APacket
{
   public:
    /**
     * @brief Construct HealthcheckPacket object that will be send to server or client.
     *
     * @return HealthcheckPacket object.
     */
    HealthcheckPacket();

    /**
     * @brief Construct new HealthcheckPacket object with serialized data by deserializing them.
     *
     * @param buffer: Serialized packet data to deserialize.
     * @return HealthcheckPacket object.
     */
    HealthcheckPacket(std::vector<char> &buffer);

    /**
     * @brief Destruct HealthcheckPacket object.
     */
    ~HealthcheckPacket();

   public:
    /**
     * @brief Serialize class data to binary to make it sendable by NetworkHandler.
     *
     * @return empty std::vector<char> because nothing to serialize.
     */
    std::vector<char> serializeData() const override;
};
}  // namespace RType::Network