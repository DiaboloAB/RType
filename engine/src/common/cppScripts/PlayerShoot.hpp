/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef PLAYERSHOOT_HPP
#define PLAYERSHOOT_HPP

#include "common/ICppScript.hpp"
#include "gameContext/GameContext.hpp"
#include "utils/Timer.hpp"

namespace RType
{

class PlayerShoot : public RType::ICppScript
{
   public:
    void update(mobs::Registry &registry, GameContext &gameContext) override
    {
        if (timer.getState())
        {
            timer.setTime(timer.getTime() + gameContext._deltaT);
        }
        if (gameContext._runtime->getKeyDown(KeyCode::Space))
        {
            timer.start();
        }
        if (gameContext._runtime->getKeyUp(KeyCode::Space))
        {
            float charge = timer.getTime();
            mobs::Entity laser = gameContext._sceneManager.instantiate("Laser", gameContext);
            auto &animator = registry.get<Animator>(laser).animations;
            auto &transform = registry.get<Transform>(laser);
            auto &hitbox = registry.get<Hitbox>(laser);

            transform.position =
                registry.get<Transform>(getEntity()).position + mlg::vec3(50, 0, 0);

            if (charge < 0.4)
            {
                animator.playAnim("small");
                hitbox.size = mlg::vec3(16, 10, 0);
                health = 1;
            }
            else if (charge < 1)
            {
                animator.playAnim("medium");
                hitbox.size = mlg::vec3(32, 12, 0);
                health = 2;
            }
            else if (charge < 1.6)
            {
                animator.playAnim("large");
                hitbox.size = mlg::vec3(48, 14, 0);
                health = 3;
            }
            else
            {
                animator.playAnim("full");
                hitbox.size = mlg::vec3(64, 14, 0);
                health = 5;
            }
            timer.reset();
            timer.stop();
        }
    }
    static constexpr const char *name = "PlayerShoot";

   private:
    Timer timer;
    int health = 1;
};

}  // namespace RType

#endif  // PLAYERSHOOT_HPP