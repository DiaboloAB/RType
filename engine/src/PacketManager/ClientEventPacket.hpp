/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#pragma once

#include "APacket.hpp"

namespace RType::Network {

/**
 * @class ClientEventPacket
 *
 * @brief Class used to create a Packet that can be serialize and deserialize. This packet hold
 * main information used to manage client events (shoot, move, ...).
 */
class ClientEventPacket : public APacket {
    public:
        /**
        * @brief Construct ClientEventPacket object that will be send to server.
        *
        * @return ClientEventPacket object.
        */
        ClientEventPacket();

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
        * @return empty std::vector<char> because nothing to serialize.
        */
        std::vector<char> serializeData() const override;
};
}
