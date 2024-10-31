/**********************************************************************************
 *  Project: Dimension Network
 *  Description: Networking Game Library
 *  Author: Morgan LARGEOT, Maxence LARGEOT
 *  Create Time: 2024-10-17
 *  Location: Rennes
 **********************************************************************************/

#pragma once

#include <asio.hpp>

#include "APacket.hpp"
#include "PacketValidation.hpp"

namespace dimension
{
/** @class IEndpoint
 *
 * @brief This class is an interface which contains all common methods between client & server
 * network communication.
 */
class IEndpoint
{
   public:
    virtual ~IEndpoint() = default;

   public:
    /**
     * @brief Send a packet to client or server and add it to a validation if needed
     *
     * @param packet: Packet to send (See: docs/rfc-53952.txt).
     * @param endpoint: Endpoint target to send packet to.
     * @param isNewPacket Determine if the packet need to be added to validation list or if it's
     * resend. Default value: true.
     */
    virtual void send(const std::shared_ptr<APacket> &packet,
                      const asio::ip::udp::endpoint &endpoint, bool isNewPacket) = 0;

   public:
    /**
     * @brief Method that pop the first element of the packet received queue if not empty.
     */
    virtual void popReceiveQueue() = 0;

    /**
     * @brief Delete packet keeped in validation list if a validation of this packet is received.
     * Does nothing if the validation correspond to any packet in the packet validation list.
     *
     * @param validation: Packet that tells information about the packet to validate.
     * @param enpoint: Enpoint from the target that needed to validate the packet.
     */
    virtual void deleteFromValidationList(const std::shared_ptr<PacketValidation> &validation,
                                          const asio::ip::udp::endpoint &endpoint) = 0;

   protected:
    /**
     * @brief Method that receive packets from an endpoint using async method from asio network
     * library and send it to the handler.
     */
    virtual void receive() = 0;

    /**
     * @brief Handler called by receive method that deserialize packets and add it to queue
     * of treatment.
     *
     * @param recvBuffer: Buffer of the packet received that will be deserialized.
     * @param remoteEndoint: Endpoint of the sender of the packet.
     * @param bytesRcv: Length of the packet received.
     */
    virtual void handleDataReceived(std::array<char, 1024> buffer, asio::ip::udp::endpoint endpoint,
                                    std::size_t bytesRcv) = 0;

    /**
     * @brief Resend packet which didn't receive any validation to appropriate target.
     */
    virtual void resendValidationList() = 0;

    /**
     * @brief Method called to handle ping sending to handle if a connection is not keep alive.
     */
    virtual void sendPing() = 0;
};
}  // namespace dimension