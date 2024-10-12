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
class GameStartEvent
{
   public:
    static bool checkSenderValidity(asio::ip::udp::endpoint &sender, GameContext &gameContext)
    {
        auto networkHandler = gameContext._networkHandler;
        if (!networkHandler || !networkHandler->getIsServer() ||
            networkHandler->getGameState() == IN_GAME)
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
        float posX = 100.0;
        float posY = 100.0;

        auto networkHandler = gameContext._networkHandler;
        networkHandler->setGameState(IN_GAME);
        auto &endpointMap = networkHandler->getEndpointMap();
        for (auto &endpoint : endpointMap)
        {
            if (endpoint.second.getConnected())
            {
                mobs::Entity newEntity =
                    gameContext._sceneManager.loadPrefab("ally.json", gameContext);
                auto &transform = registry.get<Transform>(newEntity);
                transform.position = mlg::vec3(posX, posY, 0.0f);
                auto &networkComp = registry.get<NetworkComp>(newEntity);
                networkComp.id = idHandler.generateNetworkId();
                auto entiyPacket = CreateEntityPacket(networkComp.id, posX, posY, "ally.json");
                endpoint.second.setNetworkId(networkComp.id);
                networkHandler->sendToAll(entiyPacket);
                if (posY >= 1500)
                {
                    posX += 100;
                    posY = 100;
                }
                else
                    posY += 100;
                std::cerr << "CREATE ENTITY & SEND" << std::endl;
            }
        }
    }
};
}  // namespace RType::Network
