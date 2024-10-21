/**********************************************************************************
 *  Project: Dimension Network
 *  Description: Networking Game Library
 *  Author: Morgan LARGEOT, Maxence LARGEOT
 *  Create Time: 2024-10-18
 *  Location: Rennes
  **********************************************************************************/

#include "AEndpoint.hpp"

namespace dimension {

AEndpoint::AEndpoint(std::shared_ptr<APacketFactory> &factory) : _packetFactory(factory) {}

void AEndpoint::send(std::shared_ptr<APacket> &packet, const asio::ip::udp::endpoint &endpoint)
{
    std::vector<char> packetData;
    try {
        packetData = packet->serialize();
    } catch (std::exception &e) {
        throw EndpointError(std::string("\x1B[31m[EndpointError]\x1B[0m: Packet serialization failed {")
            + e.what() + "}");
    }

    this->_socket->async_send_to(asio::buffer(packetData), endpoint,
        [this](std::error_code ec, std::size_t bytes_recvd)
        {
            if (ec)
            {
                std::cerr << "\x1B[31m[EndpointError]\x1B[0m: An error occurred while sending data." << std::endl;
                return;
            }
        });
}

void AEndpoint::receive() {
    auto remoteEndpoint = std::make_shared<asio::ip::udp::endpoint>();

    this->_socket->async_receive_from(
        asio::buffer(this->_rcvBuffer), *remoteEndpoint,
        [this, remoteEndpoint](std::error_code ec, std::size_t bytesRcv)
        {
            if (!ec)
                this->handleDataReceived(this->_rcvBuffer, *remoteEndpoint, bytesRcv);
            else
                std::cerr << "\x1B[31m[EndpointError]\x1B[0m: An error occurred while receiving data." << std::endl;
            return this->receive();
        });
};

void AEndpoint::handleDataReceived(std::array<char, 1024> &buffer, asio::ip::udp::endpoint &endpoint, std::size_t &bytesRcv)
{
    std::vector<char> packetBuffer(*buffer.begin(), *buffer.begin() + bytesRcv);
    std::shared_ptr<dimension::APacket> packet = nullptr;

    try
    {
        packet = this->_packetFactory->createPacketFromBuffer(packetBuffer);
    }
    catch (std::exception &e)
    {
        throw EndpointError(std::string("\x1B[31m[EndpointError]\x1B[0m: Packet deserialization failed {")
            + e.what() + "}");
        return;
    }

    std::lock_guard<std::mutex> lock(this->_queueMutex);
    this->_rcvQueue.push(std::make_pair(packet, endpoint));
}
}
