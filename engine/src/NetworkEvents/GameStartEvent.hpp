/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#pragma once

#include <asio.hpp>
#include <mobs/mobs.hpp>
#include <gameContext/GameContext.hpp>
#include <NetworkHandler/NetworkIdHandler.hpp>

namespace RType::Network {
    class GameStartEvent {
        public:
            static bool checkSenderValidity(asio::ip::udp::endpoint &sender, GameContext &gameContext) {
                auto networkHandler = gameContext._networkHandler;
                if (!networkHandler || !networkHandler->getIsServer() || networkHandler->getGameState() == IN_GAME)
                    return false;
                auto endpointMap = networkHandler->getEndpointMap();
                auto senderData = endpointMap.find(sender);
                if (senderData == endpointMap.end() || !senderData->second.getConnected())
                    return false;
                return true;
            }

            static void update(asio::ip::udp::endpoint &sender, mobs::Registry &registry, GameContext &gameContext,
                NetworkIdHandler &idHandler) {
                if (!checkSenderValidity(sender, gameContext))
                    return;
                float posX = 100.0;
                float posY = 100.0;
    
                auto networkHandler = gameContext._networkHandler;
                networkHandler->setGameState(IN_GAME);
                auto enpointMap = networkHandler->getEndpointMap();
                for (auto &enpoint : enpointMap) {
                    if (enpoint.second.getConnected()) {
                        mobs::Entity newEntity = gameContext._sceneManager.loadPrefab(
                            "RedShip.json", gameContext);
                        auto &transform = registry.get<Transform>(newEntity);
                        transform.position = mlg::vec3(posX, posY, 0.0f);
                        auto &networkComp = registry.get<NetworkComp>(newEntity);
                        networkComp.id = idHandler.generateNetworkId();
                        auto entiyPacket = CreateEntityPacket(networkComp.id, posX, posY, "RedShip.json");
                        enpoint.second.setNetworkId(networkComp.id);
                        networkHandler->sendToAll(entiyPacket);
                        if (posY >= 1500) {
                            posX += 100;
                            posY = 100;
                        } else
                            posY += 100;
                    }
                }
            }
    };
}
