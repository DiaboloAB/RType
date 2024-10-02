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
 * @class KickClientPacket
 *
 * @brief Class used to create a Packet that can be serialize and deserialize. This packet hold
 * main information used to kick client from server.
 */
class KickClientPacket : public APacket
{
   public:
    /**
     * @brief Construct KickClientPacket object that will be send to client.
     *
     * @param reason : Reasons why client is kick from server.
     * @return KickClientPacket object.
     */
    KickClientPacket(std::string reason);

    /**
     * @brief Construct new KickClientPacket object with serialized data by deserializing them.
     *
     * @param buffer: Serialized packet data to deserialize.
     * @return KickClientPacket object.
     */
    KickClientPacket(std::vector<char> &buffer);

    /**
     * @brief Destruct KickClientPacket object.
     */
    ~KickClientPacket();

   public:
    /**
     * @brief Serialize class data to binary to make it sendable by NetworkHandler.
     *
     * @return empty std::vector<char> because nothing to serialize.
     */
    std::vector<char> serializeData() const override;

   private:
    std::string _reason;
};
}  // namespace RType::Network
