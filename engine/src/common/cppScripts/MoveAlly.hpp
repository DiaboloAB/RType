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
        int speed = 600;
        transform.position.x += ally.moveDirection.x * speed * gameContext._deltaT;
        transform.position.y += ally.moveDirection.y * speed * gameContext._deltaT;
    }
    void setEntity(mobs::Entity entity) override { _entity = entity; }

   private:
    mobs::Entity _entity;
};

}  // namespace RType

#endif  // MOVEALLY_HPP