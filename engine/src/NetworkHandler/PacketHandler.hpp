/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#pragma once

#include <asio.hpp>
#include <list>
#include <memory>
#include <queue>
#include <typeindex>

#include "APacket.hpp"
#include "networkPacket/PacketFactory.hpp"
#include "networkPacket/packets/PacketValidationPacket.hpp"
#include "networkPacket/packets/HiClientPacket.hpp"

namespace RType::Network
{
/** @class PacketHandler
 *
 * @brief This class is used to manage all the packets communication between client & server.
 * It manage a receiveQueue and a validation list for packets which need a validation Packet.
 */
class PacketHandler
{
   public:
    PacketHandler();
    ~PacketHandler();

   public:
    /**
     * @brief Insert new packet in receive queue use to update game logic.
     *
     * @param packet: Packet receive to insert.
     * @param endpoint: Sender enpoint.
     */
    void insertToReceiveQueue(const std::shared_ptr<dimension::APacket> &packet,
                              const asio::ip::udp::endpoint &endpoint);

    /**
     * @brief pop first element of the queue (FIFO).
     */
    void popReceiveQueue();

    /**
     * @brief Insert packet that need validation to the validation list.
     *
     * @param packet: Packet which needs validation.
     * @param endpoint: Endpoint target where packet is send.
     */
    void insertToValidationList(const dimension::APacket &packet, const asio::ip::udp::endpoint &endpoint);

    /**
     * @brief Delete packet keeped in validation list if a validation of this packet is received.
     * Does nothing if the validation correspond to any packet in the packet validation list.
     *
     * @param validation: Packet that tells information about the packet it validate.
     * @param enpoint: Enpoint target that receives the validated packet.
     */
    void deleteFromValidationList(const std::shared_ptr<PacketValidationPacket> &validation,
                                  const asio::ip::udp::endpoint &endpoint);

    /**
     * @brief Verify if the new packet send needs a validation packet.
     *
     * @param packet: Packet to verify
     * @return True if packet needs a validation, false otherwise.
     */
    bool needPacketValidation(const dimension::APacket &packet) const;

   public:
    std::queue<std::pair<std::shared_ptr<dimension::APacket>, asio::ip::udp::endpoint>> getReceiveQueue()
        const;
    std::list<std::pair<const dimension::APacket &, const asio::ip::udp::endpoint &>> getValidationList()
        const;

   private:
    PacketFactory _packetFactory;
    std::queue<std::pair<std::shared_ptr<dimension::APacket>, asio::ip::udp::endpoint>> _receiveQueue;
    std::list<std::pair<const dimension::APacket &, const asio::ip::udp::endpoint &>> _validationList;
    std::list<std::type_index> _needValidation = {std::type_index(typeid(HiClientPacket))};
};
}  // namespace RType::Network
