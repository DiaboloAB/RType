/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef ANIMTHRUSTER_HPP
#define ANIMTHRUSTER_HPP

#include "common/ICppScript.hpp"
#include "gameContext/GameContext.hpp"

namespace RType
{

class AnimThrusterScript : public RType::ICppScript
{
   public:
    void update(mobs::Registry &registry, GameContext &gameContext) override
    {
        int speed = 300;
        if (gameContext._runtime->getKeyDown(KeyCode::RightArrow))
        {
            AnimationList &animations = registry.get<Animator>(_entity).animations;
            animations.playAnim("low");
        }
        if (gameContext._runtime->getKeyUp(KeyCode::RightArrow))
        {
            AnimationList &animations = registry.get<Animator>(_entity).animations;
            animations.playAnim("default");
        }
    }
    void setEntity(mobs::Entity entity) override { _entity = entity; }

   private:
    mobs::Entity _entity;
};

}  // namespace RType

#endif  // ANIMTHRUSTER_HPP