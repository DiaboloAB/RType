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
        int speed = 600;
        mobs::Registry::View view = registry.view<Ally>();
        for (auto &entity : view) {
            auto &ally = view.get<Ally>(entity);
            auto &transform = view.get<Transform>(entity);
            auto &hitbox = view.get<Hitbox>(entity);
            //std::cerr << "DIR X [" << ally.moveDirection.x << "] DIR Y [" << ally.moveDirection.y << "]" << std::endl;
            transform.position.x += ally.moveDirection.x * (speed * gameContext._deltaT);
            transform.position.y += ally.moveDirection.y * (speed * gameContext._deltaT);
            if (transform.position.x < 0)
                transform.position.x = 0;
            if (transform.position.x > 1920 - hitbox.size.x)
                transform.position.x = 1920 - hitbox.size.x;
            if (transform.position.y < 0)
                transform.position.y = 0;
            if (transform.position.y > 1080 - hitbox.size.y)
                transform.position.y = 1080 - hitbox.size.y;
        }
    }
};
}  // namespace RType

#endif  // MOVEPLAYER_HPP