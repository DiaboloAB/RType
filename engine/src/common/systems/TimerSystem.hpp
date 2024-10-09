/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef TIMERSYSTEM_H
#define TIMERSYSTEM_H

#include <system/ISystem.hpp>
#include <common/components.hpp>
// std

namespace RType
{

class TimerSystem : public ISystem
{
   public:
    TimerSystem() {}
    ~TimerSystem() {}

    void update(mobs::Registry &registry, GameContext &gameContext) override
    {
        auto view = registry.view<CoolDown>();
        for (auto entity : view)
        {
            Timer &timer = view.get<CoolDown>(entity).timer;
            if (timer.getState())
            {
                timer.setTime(timer.getTime() + gameContext._deltaT);
            }
        }
    }

   private:
    // Member variables
};

}  // namespace RType

#endif  // TIMERSYSTEM_H