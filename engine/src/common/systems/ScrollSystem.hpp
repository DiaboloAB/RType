/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef SCROLLSYSTEM_H
#define SCROLLSYSTEM_H

#include <common/components.hpp>
#include <system/ISystem.hpp>
// std

namespace RType
{

class ScrollSystem : public ISystem
{
   public:
    ScrollSystem() {}
    ~ScrollSystem() {}

    void update(mobs::Registry &registry, GameContext &gameContext) override
    {
        auto view = registry.view<Transform>();
        for (auto &entity : view)
        {
            Transform &transform = view.get<Transform>(entity);
            Basics &basics = registry.get<Basics>(entity);

            if (basics.tag == "background")
            {
                continue;
            }
            if (basics.tag == "player" && transform.position.x < 0)
            {
                continue;
            }
            if (basics.tag == "thruster" && transform.position.x < -64)
            {
                continue;
            }
            // transform.position.x -= 20 * gameContext._deltaT;
            if (transform.position.x < -100)
            {
                registry.kill(entity);
            }
        }
    }

   private:
    // Member variables
};

}  // namespace RType

#endif  // SCROLLSYSTEM_H