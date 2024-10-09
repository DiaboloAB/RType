/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef MOVETHRUSTER_HPP
#define MOVETHRUSTER_HPP

#include "common/ICppScript.hpp"
#include "gameContext/GameContext.hpp"

namespace RType
{

class MoveThrusterScript : public RType::ICppScript
{
   public:
    void update(mobs::Registry &registry, GameContext &gameContext) override
    {
        const int speed = 600;
        const int playerHeight = 16;
        const int playerWidth = 64;
        const int thrusterheight = 32;
        const int thrusterWidth = 64;

        if (gameContext._runtime->getKey(KeyCode::UpArrow))
        {
            auto &transform = registry.get<Transform>(_entity);
            if (transform.position.y < 0 - playerHeight)
            {
                transform.position.y = 0 - playerHeight;
                return;
            }
            transform.position.y -= speed * gameContext._deltaT;
        }
        if (gameContext._runtime->getKey(KeyCode::DownArrow))
        {
            auto &transform = registry.get<Transform>(_entity);
            if (transform.position.y > 1080 - thrusterheight - playerHeight)
            {
                transform.position.y = 1080 - thrusterheight - playerHeight;
                return;
            }
            transform.position.y += speed * gameContext._deltaT;
        }
        if (gameContext._runtime->getKey(KeyCode::LeftArrow))
        {
            auto &transform = registry.get<Transform>(_entity);
            if (transform.position.x < 0 - thrusterWidth)
            {
                transform.position.x = 0 - thrusterWidth;
                return;
            }
            transform.position.x -= speed * gameContext._deltaT;
        }
        if (gameContext._runtime->getKey(KeyCode::RightArrow))
        {
            auto &transform = registry.get<Transform>(_entity);
            if (transform.position.x > 1920 - playerWidth - thrusterWidth)
            {
                transform.position.x = 1920 - playerWidth - thrusterWidth;
                return;
            }
            transform.position.x += speed * gameContext._deltaT;
        }
    }
    void setEntity(mobs::Entity entity) override { _entity = entity; }

   private:
    mobs::Entity _entity;
};

}  // namespace RType

#endif  // MOVETHRUSTER_HPP