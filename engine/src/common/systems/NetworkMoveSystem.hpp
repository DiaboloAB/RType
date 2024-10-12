/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef NETWORKMOVESYSTEM_HPP
#define NETWORKMOVESYSTEM_HPP

#include <common/components.hpp>
#include <system/ISystem.hpp>

#include "gameContext/GameContext.hpp"

namespace RType
{

class NetworkMoveSystem : public ISystem
{
    public:
        NetworkMoveSystem() {};
        ~NetworkMoveSystem() {};

   public:
    void update(mobs::Registry &registry, GameContext &gameContext) override
    {
        if (!gameContext._networkHandler || !gameContext._networkHandler->getIsServer() ||
        gameContext._networkHandler->getGameState() == Network::IN_MENU)
            return;
        auto &endpointMap = gameContext._networkHandler->getEndpointMap();
        mobs::Registry::View view = registry.view<NetworkComp>();
        for (auto &endpoint : endpointMap) {
            if (endpoint.second.getConnected() == true && (endpoint.second.getDirX() != 0.0 || 
            endpoint.second.getDirY() != 0.0))
                movePlayerAndSend(endpoint.second, view, gameContext, registry);
        }
    }

    void movePlayerAndSend(RType::Network::EndpointState &endpointData, mobs::Registry::View &view,
        GameContext &gameContext, mobs::Registry &registry) {
            int speed = 600;
            auto &networkHandler = gameContext._networkHandler;
            for (auto &entity : view)
            {
                auto &networkC = view.get<NetworkComp>(entity);
                if (networkC.id != endpointData.getNetworkId())
                    continue;
                auto &transform = registry.get<Transform>(entity);
                Hitbox &hitbox = registry.get<Hitbox>(entity);
                if (endpointData.getDirY() < 0.0)
                {
                    transform.position.y -= speed * gameContext._deltaT;
                    if (transform.position.y < 0)
                        transform.position.y = 0;
                }
                if (endpointData.getDirY() > 0.0)
                {
                    transform.position.y += speed * gameContext._deltaT;
                    if (transform.position.y > 1080 - hitbox.size.y)
                        transform.position.y = 1080 - hitbox.size.y;
                }
                if (endpointData.getDirX() < 0.0)
                {
                    transform.position.x -= speed * gameContext._deltaT;
                    if (transform.position.x < 0)
                        transform.position.x = 0;
                }
                if (endpointData.getDirX() > 0.0)
                {
                    transform.position.x += speed * gameContext._deltaT;
                    if (transform.position.x > 1920 - hitbox.size.x)
                        transform.position.x = 1920 - hitbox.size.x;
                }
                gameContext._networkHandler->sendToAll(Network::MoveEntityPacket(endpointData.getNetworkId(), transform.position.x,
                transform.position.y, endpointData.getDirX(), endpointData.getDirY()));
                return;
            }
    }
};
}  // namespace RType

#endif  // MOVEPLAYER_HPP