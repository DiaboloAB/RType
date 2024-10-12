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
    class MoveUpEvent {
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
                int speed = 10;
                if (!checkSenderValidity(sender, gameContext)) return;
                auto &networkHandler = gameContext._networkHandler;
                auto senderData = networkHandler->getEndpointMap().find(sender);
                mobs::Registry::View view = registry.view<NetworkComp>();
                for (auto &entity : view)
                {
                    auto &networkC = view.get<NetworkComp>(entity);
                    if (networkC.id == senderData->second.getNetworkId()) {
                        auto &transform = registry.get<Transform>(entity);
                        if (transform.position.y < 0)
                        {
                            transform.position.y = 0;
                            networkHandler->sendToAll(MoveEntityPacket(senderData->second.getNetworkId(), transform.position.x,
                            transform.position.y, 0.0, 0.0));
                            return;
                        }
                        transform.position.y -= speed * gameContext._deltaT;
                        networkHandler->sendToAll(MoveEntityPacket(senderData->second.getNetworkId(), transform.position.x,
                        transform.position.y, 0.0, 0.0));
                        break;
                    }
                }
            }
    };
}
/**
 * int speed = 600;
        if (gameContext._runtime->getKey(KeyCode::UpArrow))
        {
            auto &transform = registry.get<Transform>(_entity);
            if (transform.position.y < 0)
            {
                transform.position.y = 0;
                return;
            }
            transform.position.y -= speed * gameContext._deltaT;
        }
        if (gameContext._runtime->getKey(KeyCode::DownArrow))
        {
            auto &transform = registry.get<Transform>(_entity);
            Hitbox &hitbox = registry.get<Hitbox>(_entity);
            if (transform.position.y > 1080 - hitbox.size.y)
            {
                transform.position.y = 1080 - hitbox.size.y;
                return;
            }
            transform.position.y += speed * gameContext._deltaT;
        }
        if (gameContext._runtime->getKey(KeyCode::LeftArrow))
        {
            auto &transform = registry.get<Transform>(_entity);
            if (transform.position.x < 0)
            {
                transform.position.x = 0;
                return;
            }
            transform.position.x -= speed * gameContext._deltaT;
        }
        if (gameContext._runtime->getKey(KeyCode::RightArrow))
        {
            auto &transform = registry.get<Transform>(_entity);
            auto &hitbox = registry.get<Hitbox>(_entity);
            if (transform.position.x > 1920 - hitbox.size.x)
            {
                transform.position.x = 1920 - hitbox.size.x;
                return;
            }
            transform.position.x += speed * gameContext._deltaT;
        }
 */