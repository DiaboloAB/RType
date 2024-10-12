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
    class StopMoveDownEvent {
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
                if (senderData->second.getDirY() < 0.0)
                    return;
                senderData->second.setDirY(senderData->second.getDirY() - 1.0);
            }
    };
}
