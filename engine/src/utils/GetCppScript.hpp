/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef GETCPPSCRIPT_H
#define GETCPPSCRIPT_H

#include <mobs/mobs.hpp>
#include <stdexcept>
#include <string>
#include <vector>

#include "common/components/components.hpp"
#include "common/components/scriptsComponent.hpp"

namespace RType
{
template <typename CppScript>
std::shared_ptr<CppScript> getCppScript(std::string tag, mobs::Registry &registry)
{
    try
    {
        mobs::Registry::View view = registry.view<Basics, CppScriptComponent>();
        for (auto entity : view)
        {
            auto &basics = view.get<Basics>(entity);
            if (basics.tag == tag)
            {
                auto &cppScript = view.get<CppScriptComponent>(entity);
                std::shared_ptr<CppScript> script = cppScript.getScript<CppScript>();
                return script;
            }
        }
        throw std::runtime_error("Tag not found: " + tag);
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error(e.what());
    }
}

template <typename CppScript>
std::shared_ptr<CppScript> getCppScriptById(mobs::Entity &entity, mobs::Registry &registry)
{
    try
    {
        mobs::Registry::View view = registry.view<Basics, CppScriptComponent>();
        for (auto _entity : view)
        {
            if (entity == _entity)
            {
                auto &cppScript = view.get<CppScriptComponent>(entity);
                std::shared_ptr<CppScript> script = cppScript.getScript<CppScript>();
                return script;
            }
        }
        throw std::runtime_error("Entity not found");
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Entity not found");
    }
}
}  // namespace RType

#endif  // GETCPPSCRIPT_H