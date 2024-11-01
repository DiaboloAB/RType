/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#pragma once

#include "AServer.hpp"
#include "PacketFactory.hpp"
#include "RoomManager.hpp"

namespace RType::Network {
    class MainServer : public dimension::AServer {
        public:
            MainServer(std::string host, unsigned int port);
            ~MainServer();

        protected:
            /**
             * @brief Handler for HiServer default packet into main server.
             * 
             * @param packet: HiServer default packet.
             */
            void handleHiServer(std::pair<std::shared_ptr<dimension::APacket>, 
                asio::ip::udp::endpoint> &packet) override;

             /**
             * @brief Handler for ClientEvent default packet into main server.
             * 
             * @param packet: ClientEvent default packet.
             */
            void handleEvent(std::pair<std::shared_ptr<dimension::APacket>, 
                asio::ip::udp::endpoint> &packet) override;

             /**
             * @brief Handler for Ping default packet into main server.
             * 
             * @param packet: Ping default packet.
             */
            void handlePing(std::pair<std::shared_ptr<dimension::APacket>, 
                asio::ip::udp::endpoint> &packet) override;
            
            /**
             * @brief Check last ping from list of clients connected to handle
             * clients that may have lost the connection with the server.
             */
            void checkLastPing() override;

            /**
             * @brief Send a ping packet to every connected client that are only connected
             * the main server.
             */
            void sendPing() override;

        public:
            /**
             * @brief Set ping clock of sender to now.
             */
            void resetPing(asio::ip::udp::endpoint &sender);

        private:
            RoomManager _roomManager;
    };
}
