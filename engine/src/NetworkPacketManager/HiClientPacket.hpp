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
 * @class HiClientPacket
 *
 * @brief Class used to create a Packet that can be serialize and deserialize. This packet hold
 * main information used to ping server from new client.
 */
class HiClientPacket : public APacket
{
   public:
    /**
     * @brief Construct HiClientPacket object that will be send to client.
     *
     * @return HiClientPacket object.
     */
    HiClientPacket();

    /**
     * @brief Construct new HiClientPacket object with serialized data by deserializing them.
     *
     * @param buffer: Serialized packet data to deserialize.
     * @return HiClientPacket object.
     */
    HiClientPacket(std::vector<char> &buffer);

    /**
     * @brief Destruct HiClientPacket object.
     */
    ~HiClientPacket();

   public:
    /**
     * @brief Serialize class data to binary to make it sendable by NetworkHandler.
     *
     * @return empty std::vector<char> because nothing to serialize.
     */
    std::vector<char> serializeData() const override;

   private:
};
}  // namespace RType::Network