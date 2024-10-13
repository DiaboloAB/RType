/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#pragma once

#include <NetworkHandler/NetworkIdHandler.hpp>
#include <asio.hpp>
#include <gameContext/GameContext.hpp>
#include <mobs/mobs.hpp>

namespace RType::Network
{
class MoveLeftEvent
{
   public:
    static bool checkSenderValidity(asio::ip::udp::endpoint &sender, GameContext &gameContext)
    {
        auto networkHandler = gameContext._networkHandler;
        if (!networkHandler || !networkHandler->getIsServer() ||
            networkHandler->getGameState() == IN_MENU)
            return false;
        auto endpointMap = networkHandler->getEndpointMap();
        auto senderData = endpointMap.find(sender);
        if (senderData == endpointMap.end() || !senderData->second.getConnected()) return false;
        return true;
    }

    static void update(asio::ip::udp::endpoint &sender, mobs::Registry &registry,
                       GameContext &gameContext, NetworkIdHandler &idHandler)
    {
        if (!checkSenderValidity(sender, gameContext)) return;
        auto &networkHandler = gameContext._networkHandler;
        auto senderData = networkHandler->getEndpointMap().find(sender);
        mobs::Registry::View view = registry.view<Ally>();
        for (auto &entity : view)
        {
            auto &networkC = view.get<NetworkComp>(entity);
            if (networkC.id == senderData->second.getNetworkId())
            {
                auto &transform = view.get<Transform>(entity);
                auto &allyComp = view.get<Ally>(entity);
                if (allyComp.moveDirection.x < 0.0) return;
                allyComp.moveDirection.x -= 1.0;
                networkHandler->sendToAll(
                    MoveEntityPacket(networkC.id, transform.position.x, transform.position.y,
                                     allyComp.moveDirection.x, allyComp.moveDirection.y));
            }
        }
    }
};
}  // namespace RType::Network
