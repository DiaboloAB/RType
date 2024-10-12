/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#pragma once

#include <NetworkEvents/GameStartEvent.hpp>
#include <NetworkEvents/MoveUpEvent.hpp>
#include <NetworkEvents/MoveDownEvent.hpp>
#include <NetworkEvents/MoveLeftEvent.hpp>
#include <NetworkEvents/MoveRightEvent.hpp>
#include <NetworkHandler/NetworkIdHandler.hpp>
#include <NetworkPacketManager/ClientEventPacket.hpp>
#include <asio.hpp>
#include <functional>
#include <gameContext/GameContext.hpp>
#include <mobs/mobs.hpp>
#include <unordered_map>

namespace RType::Network
{
class NetworkEventHandler
{
   public:
    NetworkEventHandler(NetworkIdHandler &idHandler);
    ~NetworkEventHandler();

   public:
    void update(ClientEvent event, asio::ip::udp::endpoint &sender, mobs::Registry &registry,
                GameContext &gameContext);

   private:
    std::unordered_map<ClientEvent, std::function<void(asio::ip::udp::endpoint &, mobs::Registry &,
                                                       GameContext &, NetworkIdHandler &)>>
        _eventMap;
    NetworkIdHandler _idHandler;
};
}  // namespace RType::Network
