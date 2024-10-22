/**********************************************************************************
 *   Project: Dimension Network
 *   Description: Networking Game Library
 *   Author: Morgan LARGEOT, Maxence LARGEOT
 *   Create Time: 2024-10-22
 *   Location: Rennes
   **********************************************************************************/

#pragma once

#include <thread>
#include <mutex>
#include <random>
#include <asio.hpp>

#include "IRoom.hpp"
#include "APacketFactory.hpp"

namespace dimension {
    class ARoom : public IRoom {
        public:
            ARoom(std::shared_ptr<APacketFactory> &factory);
            ~ARoom() = default;
        public:
            void start() override;
            virtual void run() = 0;
            void stop() override;
        public:
            void addToReceiveQueue(std::shared_ptr<APacket> &packet, asio::ip::udp::endpoint &endpoint) override;
            std::queue<std::pair<std::shared_ptr<APacket>, asio::ip::udp::endpoint>> getSendingQueue() const override;
            void popSendingQueue() override;
        public:
            std::string getRoomId();
            int getRoomConnected();
        protected:
            std::thread _roomThread;
            std::mutex _mutex;
            std::queue<std::pair<std::shared_ptr<APacket>, asio::ip::udp::endpoint>> _recvQueue;
            std::queue<std::pair<std::shared_ptr<APacket>, asio::ip::udp::endpoint>> _sendQueue;
            std::shared_ptr<APacketFactory> _packetFactory;
            int _connected = 0;
            bool _inInGame = false;
            std::string _roomId;
    };
}