/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef TIMERSYSTEM_H
#define TIMERSYSTEM_H

#include <system/ISystem.hpp>
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
        auto view = registry.view<Timer>();
        for (auto entity : view)
        {
            auto &timer = view.get<Timer>(entity);
            timer.time += gameContext._deltaT;
        }
    }

   private:
    // Member variables
};

}  // namespace RType

#endif  // TIMERSYSTEM_H