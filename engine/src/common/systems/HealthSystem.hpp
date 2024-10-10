/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef HEALTHSYSTEM_H
#define HEALTHSYSTEM_H

#include <common/components.hpp>
#include <system/ISystem.hpp>

#include "gameContext/GameContext.hpp"
// std

namespace RType
{
class HealthSystem : public ISystem
{
   public:
    HealthSystem(){};
    ~HealthSystem(){};

    void update(mobs::Registry &registry, GameContext &gameContext) override
    {
        auto view = registry.view<Health>();
        for (mobs::Entity entity : view)
        {
            Health &hp = view.get<Health>(entity);
            if (hp.health <= 0)
            {
                registry.kill(entity);
            }
        }
    }

   private:
    // Member variables
};

}  // namespace RType

#endif  // HEALTHSYSTEM_H