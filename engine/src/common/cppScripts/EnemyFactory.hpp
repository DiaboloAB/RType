/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef ENEMYFACTORY_HPP
#define ENEMYFACTORY_HPP

#include "common/ICppScript.hpp"
#include "gameContext/GameContext.hpp"
#include "RedShipScript.hpp"
#include "../scriptsComponent.hpp"

namespace RType
{

class EnemyFactoryScript : public RType::ICppScript
{
   public:
    void update(mobs::Registry &registry, GameContext &gameContext) override
    {
        auto &timer = registry.get<Timer>(_entity);
        if (timer.time > 2.0f) {
            timer.time = 0.0f;
            std::cout << "Enemy spawned" << std::endl;

            auto newEntity = registry.create();

            registry.emplace<Animator>(newEntity);
            registry.emplace<Transform>(newEntity, mlg::vec3(1600.0f, 500.0f, 0.0f));
            registry.emplace<CppScriptComponent>(newEntity, newEntity);
            registry.emplace<Hitbox>(newEntity, mlg::vec2(64, 64, 0));

            gameContext._runtime->loadSprite("assets/graphics/enemy/red_ship.png");

            auto &animator = registry.get<Animator>(newEntity);
            animator.animations.addAnimation(Animation("assets/graphics/enemy/red_ship.png", 8, 10.0f, mlg::vec3(32, 32, 0), mlg::vec3(2.0f, 2.0f, 0), 0.0f, "default", false));
        
            auto &scripts = registry.get<CppScriptComponent>(newEntity);
            scripts.addScript(std::make_shared<RedShipScript>());
        }
    }
    void setEntity(mobs::Entity entity) override { _entity = entity; }

   private:
    mobs::Entity _entity;
};

}  // namespace RType

#endif  // ENEMYFACTORY_HPP