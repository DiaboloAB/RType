/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef MOVEPLAYER_HPP
#define MOVEPLAYER_HPP

#include "common/ICppScript.hpp"
#include "gameContext/GameContext.hpp"

namespace RType
{

class MovePlayerScript : public RType::ICppScript
{
   public:
    void update(mobs::Registry &registry, GameContext &gameContext) override
    {
        auto &transform = registry.get<Transform>(_entity);
        auto &hitbox = registry.get<Hitbox>(_entity);
        int speed = 600;
        if (gameContext._runtime->getKey(KeyCode::UpArrow))
        {
            transform.position.y -= speed * gameContext._deltaT;
            if (transform.position.y < 0) transform.position.y = 0;
        }
        if (gameContext._runtime->getKey(KeyCode::DownArrow))
        {
            transform.position.y += speed * gameContext._deltaT;
            if (transform.position.y > 1080 - hitbox.size.y)
                transform.position.y = 1080 - hitbox.size.y;
        }
        if (gameContext._runtime->getKey(KeyCode::RightArrow))
        {
            transform.position.x += speed * gameContext._deltaT;
            if (transform.position.x > 1920 - hitbox.size.x)
                transform.position.x = 1920 - hitbox.size.x;
        }
        if (gameContext._runtime->getKey(KeyCode::LeftArrow))
        {
            transform.position.x -= speed * gameContext._deltaT;
            if (transform.position.x < 0) transform.position.x = 0;
        }
    }
    void setEntity(mobs::Entity entity) override { _entity = entity; }

   private:
    mobs::Entity _entity;
};

}  // namespace RType

#endif  // MOVEPLAYER_HPP