/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef CPPSCRIPTSSYSTEM_H
#define CPPSCRIPTSSYSTEM_H

#include <common/COMPONENTLIST.hpp>
#include <system/ISystem.hpp>

#include "common/ICppScript.hpp"
#include "common/components/scriptsComponent.hpp"
#include "gameContext/GameContext.hpp"
// std

namespace RType
{
class CppScriptsSystem : public ISystem
{
   public:
    CppScriptsSystem(){};
    ~CppScriptsSystem(){};

    void update(mobs::Registry &registry, GameContext &gameContext) override
    {
        auto view = registry.view<CppScriptComponent>();
        for (auto entity : view)
        {
            auto &scripts = view.get<CppScriptComponent>(entity);
            scripts.updateAll(registry, gameContext);
        }
    }

    void events(mobs::Registry &registry, GameContext &gameContext) override
    {
        auto view = registry.view<CppScriptComponent>();
        for (auto entity : view)
        {
            auto &scripts = view.get<CppScriptComponent>(entity);
            scripts.eventsAll(registry, gameContext);
        }
    }

   private:
    // Member variables
};

}  // namespace RType

#endif  // CPPSCRIPTSSYSTEM_H