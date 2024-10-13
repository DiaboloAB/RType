/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#pragma once

#include <common/ClientEvent.hpp>

#include "APacket.hpp"

namespace RType::Network
{
/**
 * @class ClientEventPacket
 *
 * @brief Class used to create a Packet that can be serialize and deserialize. This packet hold
 * main information used to manage client events (shoot, move, ...).
 */
class ClientEventPacket : public APacket
{
   public:
    /**
     * @brief Construct ClientEventPacket object that will be send to server.
     *
     * @param event: Network client event (GAMESTART, ...).
     * @return ClientEventPacket object.
     */
    ClientEventPacket(ClientEvent event);

    /**
     * @brief Construct new CLientEventPacket object with serialized data by deserializing them.
     *
     * @param buffer: Serialized packet data to deserialize.
     * @return ClientEventPacket object.
     */
    ClientEventPacket(std::vector<char> &buffer);

    /**
     * @brief Destruct ClientEventPacket object.
     */
    ~ClientEventPacket();

   public:
    /**
     * @brief Serialize class data to binary to make it sendable by NetworkHandler.
     *
     * @return std::vector<char> representing the serialization of _clientEvent to binary.
     */
    std::vector<char> serializeData() const override;

   public:
    ClientEvent getClientEvent() const;

   private:
    ClientEvent _clientEvent;
};
}  // namespace RType::Network
