/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "SceneManager.hpp"
#include "common/fromJson.hpp"
#include "common/fromJsonNetwork.hpp"
#include "common/COMPONENTLIST.hpp"
#include "gameContext/GameContext.hpp"
#include "common/SCRIPTLIST.hpp"
// std
#include <iostream>

using namespace RType;

template <typename T>
void addCppScriptIfExists(const std::string& scriptName, mobs::Registry& registry,
                          mobs::Entity entity)
{
    std::shared_ptr<ICppScript> script = std::make_shared<T>();
    script->setEntity(entity);
    CppScriptComponent& cppScripts = registry.get<CppScriptComponent>(entity);
    cppScripts.addScript(script);
}

template <typename... T>
void addCppScriptsToEntity(mobs::Registry& registry, mobs::Entity entity,
                           const nlohmann::json& componentData)
{
    (addCppScriptIfExists<T>(T::name, registry, entity), ...);
}

void SceneManager::createEntity(const nlohmann::json& prefabJson, mobs::Entity entity,
                                mobs::Registry& registry, GameContext& gameContext)
{
    try
    {
        bool staticObject = prefabJson.value("staticObject", false);
        std::string tag = prefabJson.value("tag", "defaultTag");
        std::string layer = prefabJson.value("layer", "defaultLayer");

        registry.emplace<Basics>(entity, tag, layer, staticObject);

        addComponentsToEntity<COMPONENT_TYPES>(prefabJson["components"], registry, entity);

        if (prefabJson["components"].contains("Scripts"))
        {
            registry.emplace<Scripts>(entity, entity);
            auto& scripts = registry.get<Scripts>(entity);
            for (const auto& script : prefabJson["components"]["Scripts"])
                scripts.add(gameContext._assetsPath + script.get<std::string>(), gameContext);
        }

        if (prefabJson.contains("CppScripts")) {
            registry.emplace<CppScriptComponent>(entity, entity);
            addCppScriptsToEntity<SCRIPT_TYPES>(registry, entity, prefabJson["CppScripts"]);
        }
            // addScriptsToEntity(registry, entity, prefabJson["CppScripts"]);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: Could not create entity: " << e.what() << std::endl;
    }
}