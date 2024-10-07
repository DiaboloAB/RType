/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef CPPSCRIPTSSYSTEM_H
#define CPPSCRIPTSSYSTEM_H

#include "gameContext/GameContext.hpp"
#include <common/components.hpp>
#include "../ICppScript.hpp"
#include <system/ISystem.hpp>
// std

namespace RType
{
class CppScriptsSystem : public ISystem
{
public:
    CppScriptsSystem() {};
    ~CppScriptsSystem() {};

    void update(mobs::Registry &registry, GameContext &gameContext) override
    {
        auto view = registry.view<CppScriptComponent>();
        for (auto entity : view)
        {
            auto &scripts = view.get<CppScriptComponent>(entity);
            scripts.updateAll(registry, gameContext);
        }
    }

private:
    // Member variables
};

}

#endif // CPPSCRIPTSSYSTEM_H