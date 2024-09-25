/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#pragma once

    #include <string>

namespace RType::Network
{
    class NetworkHandler {
        public:
            NetworkHandler();
            NetworkHandler(std::string host, unsigned int port, bool isServer);
            NetworkHandler(const NetworkHandler &obj);
            ~NetworkHandler();

        public:
            std::string getHost() const;
            unsigned int getPort() const;
            void setHost(const std::string host);
            void setPort(const unsigned int port);

        public:
            void sendData();
            void receiveData();
            void serializeData();
            void deserializeData();

        private:
            std::string _host = "";
            unsigned int port_ = 0;
            bool isServer = false;
    };
}