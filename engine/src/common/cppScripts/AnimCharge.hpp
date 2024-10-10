/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef ANIMCHARGE_HPP
#define ANIMCHARGE_HPP

#include "common/ICppScript.hpp"
#include "gameContext/GameContext.hpp"

namespace RType
{

class AnimChargeScript : public RType::ICppScript
{
   public:
    void update(mobs::Registry &registry, GameContext &gameContext) override
    {
        if (gameContext._runtime->getKeyDown(KeyCode::Space))
        {
            Animations &animations = registry.get<Animator>(_entity).animations;
            animations.playAnim("idle");
        }
        if (gameContext._runtime->getKeyUp(KeyCode::Space))
        {
            Animations &animations = registry.get<Animator>(_entity).animations;
            animations.playAnim("default");
        }
    }
    void setEntity(mobs::Entity entity) override { _entity = entity; }

   private:
    mobs::Entity _entity;
};

}  // namespace RType

#endif  // ANIMCHARGE_HPP