/**********************************************************************************
 *  Project: Dimension Network
 *  Description: Networking Game Library
 *  Author: Morgan LARGEOT, Maxence LARGEOT
 *  Create Time: 2024-10-18
 *  Location: Rennes
 **********************************************************************************/

#pragma once

#include <iostream>
#include <list>
#include <mutex>
#include <queue>

#include "IEndpoint.hpp"
#include "PacketFactory.hpp"
#include "ResendTimer.hpp"

namespace dimension
{
/** @class AEndpoint
 *
 * @brief Abstract class of IEndpoint interface.
 */
class AEndpoint : public IEndpoint
{
   public:
    AEndpoint(const std::shared_ptr<PacketFactory> &factory);
    virtual ~AEndpoint() = default;

   public:
    /**
     * @brief Send a packet to client or server and add it to a validation if needed
     *
     * @param packet: Packet to send (See: docs/rfc-53952.txt).
     * @param endpoint: Endpoint target to send packet to.
     * @param isNewPacket Determine if the packet need to be added to validation list or if it's
     * resend. Default value: true.
     */
    void send(const std::shared_ptr<APacket> &packet, const asio::ip::udp::endpoint &endpoint,
              bool isNewPacket = true) override;

   public:
    /**
     * @brief Method that pop the first element of the packet received queue if not empty.
     */
    void popReceiveQueue() override;

    /**
     * @brief Delete packet keeped in validation list if a validation of this packet is received.
     * Does nothing if the validation correspond to any packet in the packet validation list.
     *
     * @param validation: Packet that tells information about the packet to validate.
     * @param enpoint: Enpoint from the target that needed to validate the packet.
     */
    void deleteFromValidationList(const std::shared_ptr<PacketValidation> &validation,
                                  const asio::ip::udp::endpoint &endpoint) override;

   protected:
    /**
     * @brief Method that receive packets from an endpoint using async method from asio network
     * library and send it to the handler.
     */
    void receive() override;

    /**
     * @brief Handler called by receive method that deserialize packets and add it to queue
     * of treatment.
     *
     * @param recvBuffer: Buffer of the packet received that will be deserialized.
     * @param remoteEndoint: Endpoint of the sender of the packet.
     * @param bytesRcv: Length of the packet received.
     */
    void handleDataReceived(std::array<char, 1024> buffer, asio::ip::udp::endpoint endpoint,
                            std::size_t bytesRcv) override;

    /**
     * @brief Resend packet which didn't receive any validation to appropriate target.
     */
    void resendValidationList() override;

   protected:
    std::shared_ptr<asio::io_context> _io_context = nullptr;
    std::shared_ptr<asio::ip::udp::socket> _socket = nullptr;
    std::shared_ptr<PacketFactory> _packetFactory = nullptr;
    std::shared_ptr<std::thread> _recvThread = nullptr;
    std::queue<std::pair<std::shared_ptr<APacket>, asio::ip::udp::endpoint>> _rcvQueue;
    std::mutex _queueMutex;

   private:
    std::array<char, 1024> _rcvBuffer;

   private:
    std::list<std::pair<std::shared_ptr<dimension::APacket>, ResendTimer>> _validationList;
    std::mutex _listMutex;

   public:
    class EndpointError : public std::exception
    {
       public:
        EndpointError(std::string error) : _error(error){};
        ~EndpointError(){};

       private:
        const char *what() const noexcept override { return _error.c_str(); };

       private:
        std::string _error;
    };
};
}  // namespace dimension
