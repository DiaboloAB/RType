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
 * @class HiServerPacket
 *
 * @brief Class used to create a Packet that can be serialize and deserialize. This packet hold
 * main information used to ping client that connection is ok for the server.
 */
class HiServerPacket : public APacket
{
   public:
    /**
     * @brief Construct HiServerPacket object that will be send to server.
     *
     * @return HiServerPacket object.
     */
    HiServerPacket();

    /**
     * @brief Construct new HiServerPacket object with serialized data by deserializing them.
     *
     * @param buffer: Serialized packet data to deserialize.
     * @return HiServerPacket object.
     */
    HiServerPacket(std::vector<char> &buffer);

    /**
     * @brief Destruct HiServerPacket object.
     */
    ~HiServerPacket();

   public:
    /**
     * @brief Serialize class data to binary to make it sendable by NetworkHandler.
     *
     * @return empty std::vector<char> because nothing to serialize.
     */
    std::vector<char> serializeData() const override;
};
}  // namespace RType::Network