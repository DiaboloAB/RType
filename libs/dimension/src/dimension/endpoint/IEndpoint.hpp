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
class IEndpoint
{
   public:
    virtual ~IEndpoint() = default;

   public:
    virtual void send(std::shared_ptr<APacket> &packet, const asio::ip::udp::endpoint &endpoint, bool isNewPacket) = 0;

   public:
    virtual void popReceiveQueue() = 0;
    virtual void deleteFromValidationList(
        const std::shared_ptr<PacketValidation> &validation,
        const asio::ip::udp::endpoint &endpoint) = 0;

   protected:
    virtual void receive() = 0;
    virtual void handleDataReceived(std::array<char, 1024> &buffer, asio::ip::udp::endpoint &endpoint,
        std::size_t &bytesRcv) = 0;

};
}  // namespace dimension