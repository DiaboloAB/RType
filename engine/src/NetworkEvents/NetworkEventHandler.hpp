/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#pragma once

#include <unordered_map>
#include <functional>
#include <asio.hpp>
#include <NetworkPacketManager/ClientEventPacket.hpp>
#include <NetworkHandler/NetworkIdHandler.hpp>
#include <mobs/mobs.hpp>
#include <gameContext/GameContext.hpp>
#include <NetworkEvents/GameStartEvent.hpp>

namespace RType::Network {
class NetworkEventHandler {
    public:
        NetworkEventHandler(NetworkIdHandler &idHandler);
        ~NetworkEventHandler();
    public:
        void update(ClientEvent event, asio::ip::udp::endpoint &sender, mobs::Registry &registry,
                           GameContext &gameContext);
    private:
        std::unordered_map<ClientEvent, std::function<void(asio::ip::udp::endpoint &, mobs::Registry &, GameContext &, NetworkIdHandler &)>> 
            _eventMap;
        NetworkIdHandler _idHandler;
};
}
