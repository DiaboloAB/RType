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

class AnimThruster : public RType::ICppScript
{
   public:
    void update(mobs::Registry &registry, GameContext &gameContext) override
    {
        int speed = 300;
        if (gameContext._runtime->getKeyDown(KeyCode::RightArrow))
        {
            AnimationList &animations = registry.get<Animator>(getEntity()).animations;
            animations.playAnim("low");
        }
        if (gameContext._runtime->getKeyUp(KeyCode::RightArrow))
        {
            AnimationList &animations = registry.get<Animator>(getEntity()).animations;
            animations.playAnim("default");
        }
    }

    static constexpr const char *name = "AnimThruster";

   private:
    // Member variables
};

}  // namespace RType

#endif  // ANIMTHRUSTER_HPP