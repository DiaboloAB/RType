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
 * @class DestroyEntityPacket
 *
 * @brief Class used to create a Packet that can be serialize and deserialize. This packet hold
 * main information used to destroy entities.
 */
class DestroyEntityPacket : public dimension::APacket
{
   public:
    /**
     * @brief Construct DestroyEntityPacket object that will be send to sever.
     *
     * @param type packet type define by class index in packetManager registration.
     * @return empty DestroyEntityPacket object.
     */
    DestroyEntityPacket(uint8_t type);

    /**
     * @brief Construct new DestroyEntityPacket object with serialized data by deserializing them.
     *
     * @param buffer: Serialized packet data to deserialize.
     * @return DestroyEntityPacket object.
     */
    DestroyEntityPacket(std::vector<char> &buffer);

    /**
     * @brief Destruct DestroyEntityPacket object.
     */
    ~DestroyEntityPacket() override;

   public:
    /**
     * @brief Serialize class data to binary to make it sendable by NetworkHandler.
     *
     * @return std::vector<char> that represent serialization of networkId to binary.
     */
    std::vector<char> serializeData() const override;
    
   public:
    uint32_t getNetworkId() const;

    public:
        void setNetworkId(const uint32_t &networkId);

   private:
    uint32_t _networkId;
};
}  // namespace RType::Network
