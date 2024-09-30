/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#pragma once

    #include <string>
    #include <list>
    #include <asio.hpp>

namespace RType::Network
{
    class NetworkHandler {
        public:
            NetworkHandler(std::string host, unsigned int port, bool isServer);
            ~NetworkHandler();

        public:
            std::string getHost() const;
            unsigned int getPort() const;
            void setHost(const std::string host);
            void setPort(const unsigned int port);

        public:
            void sendData();
            void receiveData();

        private:
            std::string _host = "";
            unsigned int _port = 0;
            bool _isServer = false;
            std::list<asio::ip::udp::endpoint> _endpointList = {};
            asio::io_context _io_context;
            std::shared_ptr<asio::ip::udp::socket> _socket = nullptr;
    };
}
