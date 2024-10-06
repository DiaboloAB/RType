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
 * @class PacketValidationPacket
 *
 * @brief Class used to create a Packet that can be serialize and deserialize. This packet hold
 * main information used to validate the receive of a packet.
 */
class PacketValidationPacket : public APacket
{
   public:
    /**
     * @brief Construct PacketValidationPacket object that will be send to client or server.
     *
     * @return PacketValidationPacket object.
     */
    PacketValidationPacket(PacketType packetType, uint64_t packetTimeStamp);

    /**
     * @brief Construct new PacketValidationPacket object with serialized data by deserializing
     * them.
     *
     * @param buffer: Serialized packet data to deserialize.
     * @return PacketValidationPacket object.
     */
    PacketValidationPacket(std::vector<char> &buffer);

    /**
     * @brief Destruct PacketValidationPacket object.
     */
    ~PacketValidationPacket();

   public:
    /**
     * @brief Serialize class data to binary to make it sendable by NetworkHandler.
     *
     * @return std::vector<char> that represent serialization of packetType, packetTimeStamp to
     * binary.
     */
    std::vector<char> serializeData() const override;

   public:
    PacketType getPacketReceiveType() const;
    uint64_t getPacketTimeStamp() const;

   private:
    PacketType _packetReceiveType;
    uint64_t _packetTimeStamp;
};
}  // namespace RType::Network
