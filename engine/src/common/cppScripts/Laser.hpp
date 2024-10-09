/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef LASER_H
#define LASER_H

#include "common/ICppScript.hpp"
#include "gameContext/GameContext.hpp"

namespace RType
{

class LaserScript : public RType::ICppScript
{
   public:
    void update(mobs::Registry &registry, GameContext &gameContext) override
    {
        int speed = 1000;
        auto &transform = registry.get<Transform>(_entity);
        transform.position.x += speed * gameContext._deltaT;

        if (transform.position.x > 1600)
        {
            registry.kill(_entity);
        }
    }
    void setEntity(mobs::Entity entity) override { _entity = entity; }

   private:
    mobs::Entity _entity;
};

}  // namespace RType

#endif  // LASER_H