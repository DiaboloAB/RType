/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#pragma once

#include "APacket.hpp"
#include "common/PacketType.hpp"

namespace RType::Network
{

/**
 * @class PacketValidationPacket
 *
 * @brief Class used to create a Packet that can be serialize and deserialize. This packet hold
 * main information used to validate the receive of a packet.
 */
class PacketValidationPacket : public dimension::APacket
{
   public:
    /**
     * @brief Construct PacketValidationPacket object that will be send to sever.
     *
     * @param type packet type define by class index in packetManager registration.
     * @return empty PacketValidationPacket object.
     */
    PacketValidationPacket(uint8_t type);

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
     * @return std::vector<char> that represent serialization of packetReceiveType,
     * packetReceiveTimeStamp to binary.
     */
    std::vector<char> serializeData() const override;

   public:
    uint8_t getPacketReceiveType() const;
    uint64_t getPacketReceiveTimeStamp() const;

    public:
        void setPacketReceiveType(const uint8_t &receiveType);
        void setPacketReceiveTimeStamp(const uint64_t &receiveTimeStamp);

   private:
    uint8_t _packetReceiveType;
    uint64_t _packetReceiveTimeStamp;
};
}  // namespace RType::Network
