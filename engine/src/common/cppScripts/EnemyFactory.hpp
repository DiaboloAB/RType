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

namespace RType
{

class EnemyFactoryScript : public RType::ICppScript
{
   public:
    void update(mobs::Registry &registry, GameContext &gameContext) override
    {
        auto &timer = registry.get<CoolDown>(_entity).timer;
        if (timer.getTime() > 2.0f)
        {
            timer.reset();

            auto &pos = registry.get<Transform>(_entity);
            gameContext._runtime->loadSprite("assets/graphics/enemy/red_ship.png");
            mobs::Entity newEntity =
                gameContext._sceneManager.loadPrefab("RedShip.json", gameContext);

            auto &transform = registry.get<Transform>(newEntity);
            transform.position = mlg::vec3(pos.position.x, pos.position.y, 0.0f);
        }
    }
    void setEntity(mobs::Entity entity) override { _entity = entity; }

   private:
    mobs::Entity _entity;
};

}  // namespace RType

#endif  // ENEMYFACTORY_HPP