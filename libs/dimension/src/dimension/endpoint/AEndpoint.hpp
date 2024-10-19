/**********************************************************************************
 *  Project: Dimension Network
 *  Description: Networking Game Library
 *  Author: Morgan LARGEOT, Maxence LARGEOT
 *  Create Time: 2024-10-18
 *  Location: Rennes
  **********************************************************************************/

#pragma once

#include <iostream>

#include "IEndpoint.hpp"
#include "APacketFactory.hpp"

namespace dimension {
    class AEndpoint : public IEndpoint {
        public:
            AEndpoint(std::shared_ptr<APacketFactory> &factory);
            virtual ~AEndpoint() = default;

        public:
            void send(std::shared_ptr<APacket> &packet, const asio::ip::udp::endpoint &endpoint) override;

        protected:
            void receive() override;
            virtual void handleDataReceived(std::array<char, 1024> &buffer,
                asio::ip::udp::endpoint &endpoint, std::size_t &bytesRcv) = 0;

        protected:
            std::shared_ptr<asio::io_context> _io_context = nullptr;
            std::shared_ptr<asio::ip::udp::socket> _socket = nullptr;
            std::shared_ptr<APacketFactory> _packetFactory = nullptr;
            std::shared_ptr<std::thread> _recvThread = nullptr;

        private:
            std::array<char, 1024> _rcvBuffer;

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
}
