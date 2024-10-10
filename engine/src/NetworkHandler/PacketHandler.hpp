/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#pragma once

#include <NetworkPacketManager/APacket.hpp>
#include <NetworkPacketManager/PacketValidationPacket.hpp>
#include <asio.hpp>
#include <list>
#include <memory>
#include <queue>

namespace RType::Network
{
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
    void insertToReceiveQueue(const std::shared_ptr<APacket> &packet,
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
    void insertToValidationList(const APacket &packet, const asio::ip::udp::endpoint &endpoint);

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
    bool needPacketValidation(const APacket &packet) const;

   public:
    std::queue<std::pair<std::shared_ptr<APacket>, asio::ip::udp::endpoint>> getReceiveQueue()
        const;
    std::list<std::pair<const APacket &, const asio::ip::udp::endpoint &>> getValidationList()
        const;

   private:
    std::queue<std::pair<std::shared_ptr<APacket>, asio::ip::udp::endpoint>> _receiveQueue;
    std::list<std::pair<const APacket &, const asio::ip::udp::endpoint &>> _validationList;
    std::list<PacketType> _needValidation = {HICLIENT, CREATEENTITY, DESTROYENTITY};
};
}  // namespace RType::Network
