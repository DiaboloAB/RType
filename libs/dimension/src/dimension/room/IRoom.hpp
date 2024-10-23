/**********************************************************************************
 *   Project: Dimension Network
 *   Description: Networking Game Library
 *   Author: Morgan LARGEOT, Maxence LARGEOT
 *   Create Time: 2024-10-22
 *   Location: Rennes
   **********************************************************************************/

#pragma once

#include <queue>

#include "APacket.hpp"

namespace dimension {
    class IRoom {
        public:
            virtual ~IRoom() = default;
        public:
            virtual void start() = 0;
            virtual void run() = 0;
            virtual void stop() = 0;
        public:
            virtual void addToReceiveQueue(std::shared_ptr<APacket> &packet, asio::ip::udp::endpoint &endpoint) = 0;
            virtual std::queue<std::pair<std::shared_ptr<APacket>, asio::ip::udp::endpoint>> getSendingQueue() const = 0;
            virtual void popSendingQueue() = 0;
            virtual bool endpointInRoom(asio::ip::udp::endpoint &endpoint) = 0;
        public:
            virtual std::string getRoomId() = 0;
            virtual int getRoomConnected() = 0;
    };
}