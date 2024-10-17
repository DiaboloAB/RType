/**********************************************************************************
 *  Project: Dimension Network
 *  Description: Networking Game Library
 *  Author: Morgan LARGEOT, Maxence LARGEOT
 *  Create Time: 2024-10-17
 *  Location: Rennes
  **********************************************************************************/

#pragma once

#include <exception>
#include <string>

namespace dimension {
    class Client {
        public:
            Client();
            ~Client();
        public:
            void connect();
            void disconnect();
            void sendPacket();
            void receivePacket();
        public:
            class NetworkClientError : public std::exception {
                public:
                    NetworkClientError(std::string msg) : _msg(msg){};
                    ~NetworkClientError(){};

                private:
                    const char *what() const noexcept override { return _msg.c_str(); };

                private:
                    std::string _msg;
            };
        private:
    };
}
