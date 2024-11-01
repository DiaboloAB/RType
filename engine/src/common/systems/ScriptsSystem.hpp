/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef SCRIPTSSYSTEM_H
#define SCRIPTSSYSTEM_H

#include <common/COMPONENTLIST.hpp>
#include <system/ISystem.hpp>
// std

namespace RType
{

class ScriptSystem : public ISystem
{
   public:
    ScriptSystem() {}
    ~ScriptSystem() {}

    void start(mobs::Registry &registry, GameContext &gameContext) override {}

    void load(mobs::Registry &registry, GameContext &gameContext) override
    {
        auto view = registry.view<Scripts>();
        for (auto entity : view)
        {
            auto &scripts = view.get<Scripts>(entity);
            scripts.loadAll(registry, gameContext);
        }
    }

    void update(mobs::Registry &registry, GameContext &gameContext) override
    {
        auto view = registry.view<Scripts>();
        for (auto entity : view)
        {
            auto &scripts = view.get<Scripts>(entity);
            scripts.updateAll(registry, gameContext);
        }
    }

    void stop(mobs::Registry &registry, GameContext &gameContext) override {
        auto view = registry.view<Scripts>();
        for (auto entity : view)
        {
            auto &scripts = view.get<Scripts>(entity);
            scripts.stopAll(registry, gameContext);
        }
    }

   private:
};

}  // namespace RType

#endif  // SCRIPTSSYSTEM_H