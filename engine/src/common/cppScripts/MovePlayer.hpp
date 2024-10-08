/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef MovePlayer_HPP
#define MovePlayer_HPP

#include "common/ICppScript.hpp"
#include "gameContext/GameContext.hpp"

namespace RType
{

class MovePlayerScript : public RType::ICppScript
{
   public:
    void update(mobs::Registry &registry, GameContext &gameContext) override
    {
        int speed = 1000;
        if (gameContext._runtime->getKey(KeyCode::UpArrow))
        {
            auto &transform = registry.get<Transform>(_entity);
            transform.position.y -= speed * gameContext._deltaT;
        }
        if (gameContext._runtime->getKey(KeyCode::DownArrow))
        {
            auto &transform = registry.get<Transform>(_entity);
            transform.position.y += speed * gameContext._deltaT;
        }
        if (gameContext._runtime->getKey(KeyCode::LeftArrow))
        {
            auto &transform = registry.get<Transform>(_entity);
            transform.position.x -= speed * gameContext._deltaT;
        }
        if (gameContext._runtime->getKey(KeyCode::RightArrow))
        {
            auto &transform = registry.get<Transform>(_entity);
            transform.position.x += speed * gameContext._deltaT;
        }
    }
    void setEntity(mobs::Entity entity) override { _entity = entity; }

   private:
    mobs::Entity _entity;
};

}  // namespace RType

#endif  // MovePlayer_HPP