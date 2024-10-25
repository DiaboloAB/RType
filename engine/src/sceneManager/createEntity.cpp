/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "SceneManager.hpp"
#include "common/components.hpp"
#include "common/fromJson.hpp"
#include "common/fromJsonNetwork.hpp"
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
        bool staticObject = prefabJson.value("staticObject", false);
        std::string tag = prefabJson.value("tag", "defaultTag");
        std::string layer = prefabJson.value("layer", "defaultLayer");

        registry.emplace<Basics>(entity, tag, layer, staticObject);

        addComponentIfExists<Transform>("Transform", prefabJson["components"], registry, entity);
        addComponentIfExists<Sprite>("Sprite", prefabJson["components"], registry, entity);
        addComponentIfExists<Animator>("Animator", prefabJson["components"], registry, entity);
        addComponentIfExists<Sticky>("Sticky", prefabJson["components"], registry, entity);
        addComponentIfExists<NetworkClient>("NetworkClient", prefabJson["components"], registry,
                                            entity);

        if (prefabJson["components"].contains("Scripts"))
        {
            registry.emplace<Scripts>(entity);
            auto& scripts = registry.get<Scripts>(entity);
            for (const auto& script : prefabJson["components"]["Scripts"])
                scripts.add(gameContext._assetsPath + script.get<std::string>(), gameContext);
        }

        if (prefabJson.contains("CppScripts"))
            addScriptsToEntity(registry, entity, prefabJson["CppScripts"]);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: Could not create entity: " << e.what() << std::endl;
    }
}