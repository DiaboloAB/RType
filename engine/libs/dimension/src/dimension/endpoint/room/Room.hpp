/**********************************************************************************
 *   Project: Dimension Network
 *   Description: Networking Game Library
 *   Author: Morgan LARGEOT, Maxence LARGEOT
 *   Create Time: 2024-10-27
 *   Location: Rennes
   **********************************************************************************/

#pragma once

#include <string>
#include <chrono>
#include <list>
#include <asio.hpp>

#include "AEndpoint.hpp"

namespace dimension {
    class Room : public AEndpoint {
        public:
            Room(const std::shared_ptr<PacketFactory> &factory, std::string host, unsigned int port,
                std::string code);
            ~Room();

        public:
            void pingEndpoints();

        public:
            void addSenderToRoom(asio::ip::udp::endpoint &sender);
            /**
             * @brief Check if a client is connected to the server.
             * 
             * @param endpoint: Endpoint of the client to ckeck.
             * @return true 
             * @return false 
             */
            bool isConnected(asio::ip::udp::endpoint &endpoint) const;


        public:
            std::string getHost() const { return this->_host; };
            unsigned int getPort() const { return this->_port; };
            std::string getCode() const { return this->_code; };
            std::list<std::pair<asio::ip::udp::endpoint, std::chrono::steady_clock::time_point>> 
                getConnectedEp() const { return this->_connectedEp; };
            std::chrono::steady_clock::time_point getLastPing() { return this->_lastPing; };
            std::queue<std::pair<std::shared_ptr<APacket>, asio::ip::udp::endpoint>> 
                getRecvQueue() { return this->_rcvQueue; };

        private:
            std::string _host;
            unsigned int _port;
            std::string _code;
            std::list<std::pair<asio::ip::udp::endpoint, std::chrono::steady_clock::time_point>> _connectedEp;
            std::chrono::steady_clock::time_point _lastPing;
    };
}