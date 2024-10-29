/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef ANIMLASERCHARGE_HPP
#define ANIMLASERCHARGE_HPP

#include "common/ICppScript.hpp"
#include "gameContext/GameContext.hpp"
#include "utils/Timer.hpp"

namespace RType
{

class AnimLaserCharge : public RType::ICppScript
{
   public:
    void update(mobs::Registry &registry, GameContext &gameContext) override
    {
        if (gameContext._runtime->getKeyDown(KeyCode::Space))
        {
            timer.start();
        }
        if (timer.getState())
        {
            timer.setTime(timer.getTime() + gameContext._deltaT);
            if (!animPlay && timer.getTime() > 0.2f)
            {
                AnimationList &animations = registry.get<Animator>(getEntity()).animations;
                animations.playAnim("charging");
                animPlay = true;
            }
            if (timer.getTime() > 1.6f)
            {
                timer.stop();
                timer.reset();
                AnimationList &animations = registry.get<Animator>(getEntity()).animations;
                animations.playAnim("charged");
            }
        }

        if (gameContext._runtime->getKeyUp(KeyCode::Space))
        {
            timer.stop();
            timer.reset();
            AnimationList &animations = registry.get<Animator>(getEntity()).animations;
            animations.playAnim("default");
            animPlay = false;
        }
    }

    static constexpr const char *name = "AnimLaserCharge";

   private:
    Timer timer;
    bool animPlay = false;
};

}  // namespace RType

#endif  // ANIMLASERCHARGE_HPP