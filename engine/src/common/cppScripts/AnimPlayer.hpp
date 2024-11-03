/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef ANIMPLAYER_HPP
#define ANIMPLAYER_HPP

#include "common/ICppScript.hpp"
#include "gameContext/GameContext.hpp"

namespace RType
{

class AnimPlayer : public RType::ICppScript
{
   public:
    void update(mobs::Registry &registry, GameContext &gameContext) override
    {
        int speed = 300;
        if (gameContext._runtime->getKeyDown(KeyCode::UpArrow))
        {
            AnimationList &animations = registry.get<Animator>(getEntity()).animations;
            animations.playAnim("up");
        }
        if (gameContext._runtime->getKeyUp(KeyCode::UpArrow))
        {
            AnimationList &animations = registry.get<Animator>(getEntity()).animations;
            animations.playAnim("default");
        }
        if (gameContext._runtime->getKeyDown(KeyCode::DownArrow))
        {
            AnimationList &animations = registry.get<Animator>(getEntity()).animations;
            animations.playAnim("down");
        }
        if (gameContext._runtime->getKeyUp(KeyCode::DownArrow))
        {
            AnimationList &animations = registry.get<Animator>(getEntity()).animations;
            animations.playAnim("default");
        }
    }

    static constexpr const char *name = "AnimPlayer";

   private:
    // Member variables
};

}  // namespace RType

#endif  // ANIMPLAYER_HPP