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
            std::cout << "Space released at: " << timer.getTime() << std::endl;
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