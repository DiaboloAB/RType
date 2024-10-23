/**********************************************************************************
 *   Project: Dimension Network
 *   Description: Networking Game Library
 *   Author: Morgan LARGEOT, Maxence LARGEOT
 *   Create Time: 2024-10-22
 *   Location: Rennes
   **********************************************************************************/

#include "ARoom.hpp"

namespace dimension {
ARoom::ARoom(std::shared_ptr<APacketFactory> &factory) : _packetFactory(factory) {
    const std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, chars.size() - 1);

    for (int i = 0; i < 6; i++)
        this->_roomId += chars[distrib(gen)];
}

void ARoom::start() {
    this->_roomThread = std::thread(&ARoom::run, this);
}

void ARoom::stop() {
    if (this->_roomThread.joinable())
        this->_roomThread.join();
}

void ARoom::addToReceiveQueue(std::shared_ptr<APacket> &packet, asio::ip::udp::endpoint &endpoint) {
    std::lock_guard<std::mutex>(this->_mutex);
    this->_recvQueue.push(std::make_pair(packet, endpoint));
}

std::queue<std::pair<std::shared_ptr<APacket>, asio::ip::udp::endpoint>> ARoom::getSendingQueue() const
{
    return this->_sendQueue;
}

void ARoom::popSendingQueue() {
    std::lock_guard<std::mutex>(this->_mutex);
    this->_sendQueue.pop();
}

std::string ARoom::getRoomId() { return this->_roomId; };

int ARoom::getRoomConnected() { return this->_connectedNumber; };

bool ARoom::endpointInRoom(asio::ip::udp::endpoint &endpoint)
{
    for (auto &enpointCo : this->_connectedEndpoints) {
        if (enpointCo == endpoint)
            return true;
    }
    return false;
}
}