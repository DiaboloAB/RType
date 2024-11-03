/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef EXPLOSION_HPP
#define EXPLOSION_HPP

#include "common/ICppScript.hpp"
#include "gameContext/GameContext.hpp"

namespace RType
{

class Explosion : public RType::ICppScript
{
   public:

    void start(mobs::Registry &registry, GameContext &gameContext) override
    {
        auto &animations = registry.get<Animator>(getEntity()).animations;
        animations.playAnim("explosion");
    }

    void update(mobs::Registry &registry, GameContext &gameContext) override
    {
        auto &animations = registry.get<Animator>(getEntity()).animations;

        if (animations.getCurrentAnim() == "default")
        {
            registry.kill(getEntity());
        }
    }

    static constexpr const char *name = "Explosion";

   private:

};

}  // namespace RType

#endif  // EXPLOSION_HPP