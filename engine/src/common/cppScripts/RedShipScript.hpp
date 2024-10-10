/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef REDSHIP_HPP
#define REDSHIP_HPP

#include "common/ICppScript.hpp"
#include "gameContext/GameContext.hpp"

namespace RType
{

class RedShipScript : public RType::ICppScript
{
   public:
    void update(mobs::Registry &registry, GameContext &gameContext) override
    {
        int speed = 100;
        auto &transform = registry.get<Transform>(_entity);
        transform.position.x -= speed * gameContext._deltaT;
    }
    void setEntity(mobs::Entity entity) override { _entity = entity; }

   private:
    mobs::Entity _entity;
};

}  // namespace RType

#endif  // REDSHIP_HPP