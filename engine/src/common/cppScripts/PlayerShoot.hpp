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

namespace RType
{

class PlayerShootScript : public RType::ICppScript
{
   public:
    void update(mobs::Registry &registry, GameContext &gameContext) override
    {
        Timer &timer = registry.get<CoolDown>(_entity).timer;
        if (gameContext._runtime->getKeyDown(KeyCode::Space))
        {
            timer.start();
        }
        if (gameContext._runtime->getKeyUp(KeyCode::Space))
        {
            float charge = timer.getTime();
            mobs::Entity laser = gameContext._sceneManager.loadPrefab("Laser.json", gameContext);
            auto &animator = registry.get<Animator>(laser).animations;
            auto &transform = registry.get<Transform>(laser);
            auto &hitbox = registry.get<Hitbox>(laser);
            auto &health = registry.get<Health>(laser);

            transform.position = registry.get<Transform>(_entity).position + mlg::vec3(50, 0, 0);
            if (charge < 0.4)
            {
                gameContext._runtime->loadSprite("assets/graphics/player/beam/small.png");
            }
            else if (charge < 0.8)
            {
                gameContext._runtime->loadSprite("assets/graphics/player/beam/medium.png");
                animator.playAnim("medium");
                hitbox.size = mlg::vec3(64, 24, 0);
                health.health = 2;
            }
            else if (charge < 1.2)
            {
                gameContext._runtime->loadSprite("assets/graphics/player/beam/large.png");
                animator.playAnim("large");
                hitbox.size = mlg::vec3(96, 28, 0);
                health.health = 3;
            }
            else
            {
                gameContext._runtime->loadSprite("assets/graphics/player/beam/full.png");
                animator.playAnim("full");
                hitbox.size = mlg::vec3(128, 28, 0);
                health.health = 5;
            }
            timer.reset();
            timer.stop();
        }
    }
    void setEntity(mobs::Entity entity) override { _entity = entity; }

   private:
    mobs::Entity _entity;
};

}  // namespace RType

#endif  // PLAYERSHOOT_HPP