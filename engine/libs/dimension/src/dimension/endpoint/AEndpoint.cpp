/**********************************************************************************
 *  Project: Dimension Network
 *  Description: Networking Game Library
 *  Author: Morgan LARGEOT, Maxence LARGEOT
 *  Create Time: 2024-10-18
 *  Location: Rennes
 **********************************************************************************/

#include "AEndpoint.hpp"

namespace dimension
{

AEndpoint::AEndpoint(const std::shared_ptr<PacketFactory> &factory) : _packetFactory(factory) {}

void AEndpoint::send(const std::shared_ptr<APacket> &packet,
                     const asio::ip::udp::endpoint &endpoint, bool isNewPacket)
{
    std::vector<char> packetData;
    try
    {
        packetData = packet->serialize();
    }
    catch (std::exception &e)
    {
        throw EndpointError(
            std::string("\x1B[31m[EndpointError]\x1B[0m: Packet serialization failed {") +
            e.what() + "}");
    }
    if (isNewPacket)
    {
        std::lock_guard<std::mutex> lock(this->_listMutex);
        this->_validationList.insert(this->_validationList.end(),
                                     std::make_pair(packet, ResendTimer(endpoint)));
    }
    this->_socket->async_send_to(
        asio::buffer(packetData), endpoint,
        [this](std::error_code ec, std::size_t bytes_recvd)
        {
            if (ec)
            {
                ERR_LOG("AEndpoint", "An error occurred while sending data. {" + ec.message() + "}");
                return;
            }
        });
}

void AEndpoint::receive()
{
    auto remoteEndpoint = std::make_shared<asio::ip::udp::endpoint>();

    this->_socket->async_receive_from(
        asio::buffer(this->_rcvBuffer), *remoteEndpoint,
        [this, remoteEndpoint](std::error_code ec, std::size_t bytesRcv)
        {
            if (!ec)
            {
                this->handleDataReceived(this->_rcvBuffer, *remoteEndpoint, bytesRcv);
            }
            else
                ERR_LOG("AEndpoint", "An error occurred while receiving data. {" + ec.message() + "}");
            return this->receive();
        });
};

void AEndpoint::handleDataReceived(std::array<char, 1024> buffer, asio::ip::udp::endpoint endpoint,
                                   std::size_t bytesRcv)
{
    std::vector<char> packetBuffer(buffer.begin(), buffer.begin() + bytesRcv);
    std::shared_ptr<dimension::APacket> packet = nullptr;

    try
    {
        packet = this->_packetFactory->createPacketFromBuffer(packetBuffer);
    }
    catch (std::exception &e)
    {
        throw EndpointError(
            std::string("\x1B[31m[EndpointError]\x1B[0m: Packet deserialization failed {") +
            e.what() + "}");
        return;
    }
    if (this->_packetFactory->getTypeFromIndex(std::type_index(typeid(PacketValidation))) ==
        packet->getPacketType())
        return this->deleteFromValidationList(std::static_pointer_cast<PacketValidation>(packet),
                                              endpoint);
    std::lock_guard<std::mutex> lock(this->_queueMutex);
    this->_rcvQueue.push(std::make_pair(packet, endpoint));
    LOG("AEndpoint", "Packet received {type: " + std::to_string(packet->getPacketType()) + "}");
}

void AEndpoint::popReceiveQueue()
{
    if (!this->_rcvQueue.empty())
    {
        std::lock_guard<std::mutex> lock(this->_queueMutex);
        this->_rcvQueue.pop();
    }
}

void AEndpoint::deleteFromValidationList(const std::shared_ptr<PacketValidation> &validation,
                                         const asio::ip::udp::endpoint &endpoint)
{
    for (auto packetInValidation = this->_validationList.begin();
         packetInValidation != this->_validationList.end();)
    {
        uint8_t packetType = packetInValidation->first->getPacketType();
        uint64_t packetTimeStamp = packetInValidation->first->getPacketTimeStamp();
        if (validation->getPacketReceiveType() == packetType &&
            validation->getPacketReceiveTimeStamp() == packetTimeStamp &&
            endpoint == packetInValidation->second._sender)
        {
            std::lock_guard<std::mutex> lock(this->_listMutex);
            this->_validationList.erase(packetInValidation);
            LOG("AEndpoint", "Validation received for -> " + std::to_string(validation->getPacketReceiveType()));
            return;
        }
        else
            packetInValidation++;
    }
}

void AEndpoint::resendValidationList()
{
    std::chrono::steady_clock::time_point time = std::chrono::steady_clock::now();
    std::lock_guard<std::mutex> lock(this->_listMutex);
    for (auto &validation : this->_validationList)
        if (std::chrono::duration_cast<std::chrono::milliseconds>(time - validation.second._timer)
                .count() >= 20)
        {
            this->send(validation.first, validation.second._sender, false);
            validation.second._timer = std::chrono::steady_clock::now();
        }
}
}  // namespace dimension
