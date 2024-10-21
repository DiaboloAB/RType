/**********************************************************************************
 *  Project: Dimension Network
 *  Description: Networking Game Library
 *  Author: Morgan LARGEOT, Maxence LARGEOT
 *  Create Time: 2024-10-18
 *  Location: Rennes
  **********************************************************************************/

#pragma once

#include "AdiosServer.hpp"
#include "HiServer.hpp"
#include "HiClient.hpp"
#include "CreateEntity.hpp"
#include "DestroyEntity.hpp"
#include "MoveEntity.hpp"
#include "ClientEvent.hpp"
#include "PacketValidation.hpp"
#include "UpdateEntity.hpp"
#include "Ping.hpp"

#include "PacketManager.hpp"

namespace dimension
{

/**
 * @class APacketFactory
 *
 * @brief This class is a design pattern use to create all types of packets. These packets
 * are used for network communication between client and server.
 */
class APacketFactory
{
   public:
    APacketFactory();
    virtual ~APacketFactory() = default;

   public:
    /**
     * @brief Create a new packet with the buffer passed as parameter.
     *
     * @param buffer : Serialized data used to create a packet.
     * @return Pointer in a deserialized packet or throw an error if invalid packet.
     */
    std::shared_ptr<APacket> createPacketFromBuffer(std::vector<char> &buffer) {
        try {
            return this->_packetManager.createPacketFromBuffer(buffer);
        } catch (std::exception &e) {
            throw;
        }
    };

    /**
     * @brief Creates an empty packet of the specified type to be sent.
     *
     * Utilizes the provided packet type to instantiate an empty packet object,
     * facilitating the preparation and dispatch of network data.
     *
     * @tparam Packet The type of the packet to be created.
     * @return std::shared_ptr<Packet> A shared pointer to the newly created packet.
     */
    template<typename Packet>
    std::shared_ptr<Packet> createEmptyPacket() {
        try {
            return this->_packetManager.createPacketToSend<Packet>();
        } catch (std::exception &e) {
            throw;
        }
    }

    public:
        std::type_index getIndexFromType(uint8_t packetType) const {
            try {
                return this->_packetManager.getIndexFromType(packetType);
            } catch (std::exception &e) {
                throw;
            }
        }

        uint8_t getTypeFromIndex(std::type_index packetIndex) const {
            try {
                return this->_packetManager.getTypeFromIndex(packetIndex);
            } catch (std::exception &e) {
                throw;
            }
        }

   protected:
    PacketManager _packetManager;
};
}  // namespace RType::Network
