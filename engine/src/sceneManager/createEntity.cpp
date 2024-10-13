/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "SceneManager.hpp"
#include "common/components.hpp"
#include "common/scriptsComponent.hpp"
#include "gameContext/GameContext.hpp"
// std
#include <iostream>

using namespace RType;

void SceneManager::createEntity(const nlohmann::json& prefabJson, mobs::Entity entity,
                                mobs::Registry& registry, GameContext& gameContext)
{
    try
    {
        bool staticObject = false;
        std::string tag = "defaultTag";

        try
        {
            staticObject = prefabJson["staticObject"].get<bool>();
        }
        catch (const std::exception& e)
        {
            staticObject = false;
        }

        try
        {
            tag = prefabJson["tag"].get<std::string>();
        }
        catch (const std::exception& e)
        {
            tag = "defaultTag";
        }

        registry.emplace<Basics>(entity, tag, staticObject);

        for (const auto& componentJson : prefabJson["components"].items())
        {
            try
            {
                const std::string& componentName = componentJson.key();
                const auto& data = componentJson.value();

                if (componentName == "Scripts")
                {
                    registry.emplace<Scripts>(entity);
                    auto& scripts = registry.get<Scripts>(entity);
                    for (const auto& script : data)
                    {
                        scripts.addScript(script.get<std::string>(), gameContext);
                    }
                }
                if (componentName == "CppScripts")
                {
                    addScriptsToEntity(registry, entity, data);
                }
                auto it = _componentCreators.find(componentName);
                if (it != _componentCreators.end())
                {
                    it->second(registry, entity, data);
                }
            }
            catch (const std::exception& e)
            {
                std::cerr << "Error: Could not create component" << std::endl;
            }
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: Could not create entity" << std::endl;
    }
}