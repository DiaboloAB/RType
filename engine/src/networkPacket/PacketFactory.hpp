/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#pragma once

#include <exception>
#include <functional>
#include <memory>
#include <unordered_map>

#include "PacketManager.hpp"

#include "networkPacket/packets/AdiosServerPacket.hpp"
#include "networkPacket/packets/ClientEventPacket.hpp"
#include "networkPacket/packets/CreateEntityPacket.hpp"
#include "networkPacket/packets/DestroyEntityPacket.hpp"
#include "networkPacket/packets/HiClientPacket.hpp"
#include "networkPacket/packets/HiServerPacket.hpp"
#include "networkPacket/packets/MoveEntityPacket.hpp"
#include "networkPacket/packets/PacketValidationPacket.hpp"
#include "networkPacket/packets/PingPacket.hpp"
#include "networkPacket/packets/UpdateEntityPacket.hpp"

namespace RType::Network
{

/**
 * @class PacketFactory
 *
 * @brief This class is a design pattern use to create all types of packets. These packets
 * are used for network communication between client and server.
 */
class PacketFactory
{
   public:
    PacketFactory();
    ~PacketFactory();

   public:
    /**
     * @brief Create a new packet with the buffer passed as parameter.
     *
     * @param buffer : Serialized data used to create a packet.
     * @return Pointer in a deserialized packet or throw an error if invalid packet.
     */
    std::shared_ptr<dimension::APacket> createPacketFromBuffer(std::vector<char> &buffer) {
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

   private:
    dimension::PacketManager _packetManager;
};
}  // namespace RType::Network
