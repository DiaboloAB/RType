/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef MOVEALLY_HPP
#define MOVEALLY_HPP

#include "common/ICppScript.hpp"
#include "gameContext/GameContext.hpp"

namespace RType
{

class MoveAllyScript : public RType::ICppScript
{
   public:
    void update(mobs::Registry &registry, GameContext &gameContext) override
    {
        auto &transform = registry.get<Transform>(_entity);
        auto &ally = registry.get<Ally>(_entity);
        auto &hitbox = registry.get<Hitbox>(_entity);
        int speed = 600;
        transform.position.x += ally.moveDirection.x * (speed * gameContext._deltaT);
        transform.position.y += ally.moveDirection.y * (speed * gameContext._deltaT);
            //std::cerr << "DIR X [" << ally.moveDirection.x << "] DIR Y [" << ally.moveDirection.y << "]" << std::endl;
        if (transform.position.x < 0)
            transform.position.x = 0;
        if (transform.position.x > 1920 - hitbox.size.x)
            transform.position.x = 1920 - hitbox.size.x;
        if (transform.position.y < 0)
            transform.position.y = 0;
        if (transform.position.y > 1080 - hitbox.size.y)
            transform.position.y = 1080 - hitbox.size.y;
    }

    void setEntity(mobs::Entity entity) override { _entity = entity; }

   private:
    mobs::Entity _entity;
};

}  // namespace RType

#endif  // MOVEALLY_HPP