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
 * @class PacketValidation
 *
 * @brief Class used to create a Packet that can be serialize and deserialize. This packet hold
 * main information used to validate the receive of a packet.
 */
class PacketValidation : public APacket
{
   public:
    /**
     * @brief Construct PacketValidation object that will be send to sever.
     *
     * @param type packet type define by class index in packetManager registration.
     * @return empty PacketValidation object.
     */
    PacketValidation(uint8_t type);

    /**
     * @brief Construct new PacketValidation object with serialized data by deserializing
     * them.
     *
     * @param buffer: Serialized packet data to deserialize.
     * @return PacketValidation object.
     */
    PacketValidation(std::vector<char> &buffer);

    /**
     * @brief Destruct PacketValidation object.
     */
    ~PacketValidation();

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
}  // namespace dimension
