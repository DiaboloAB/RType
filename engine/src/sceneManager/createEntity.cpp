/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "SceneManager.hpp"
#include "common/COMPONENTLIST.hpp"
#include "common/FROMJSON.hpp"
#include "common/SCRIPTLIST.hpp"
#include "gameContext/GameContext.hpp"
// std
#include <iostream>

using namespace RType;

template <typename T>
static void addCppScriptIfExists(const nlohmann::json& data, mobs::Registry& registry,
                                 mobs::Entity entity)
{
    // std::cout << "Checking for CppScript: " << T::name << std::endl;
    for (const auto& script : data)
    {
        if (script.get<std::string>() == T::name)
        {
            // std::cout << "Adding CppScript: " << T::name << std::endl;
            auto script = std::make_shared<T>();
            registry.get<CppScriptComponent>(entity).addScript(script);
        }
    }
}

template <typename... T>
static void addCppScriptsToEntity(mobs::Registry& registry, mobs::Entity entity,
                                  const nlohmann::json& componentData)
{
    // std::cout << componentData << std::endl;
    (addCppScriptIfExists<T>(componentData, registry, entity), ...);
}

template <typename T>
static void addComponentIfExists(const nlohmann::json& data, mobs::Registry& registry,
                                 mobs::Entity entity)
{
    if (data.contains(T::name))
    {
        T component;
        data.at(T::name).get_to(component);
        registry.emplace<T>(entity, component);
    }
}

template <typename... T>
static void addComponentsToEntity(const nlohmann::json& componentData, mobs::Registry& registry,
                                  mobs::Entity entity)
{
    (addComponentIfExists<T>(componentData, registry, entity), ...);
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

        if (prefabJson.contains("CppScripts"))
        {
            registry.emplace<CppScriptComponent>(entity, entity);
            // std::cout << "Adding CppScripts to entity" << std::endl;
            addCppScriptsToEntity<SCRIPT_TYPES>(registry, entity, prefabJson["CppScripts"]);
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: Could not create entity: " << e.what() << std::endl;
    }
}