/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "SceneManager.hpp"

#include "common/COMPONENTLIST.hpp"
#include "common/components/scriptsComponent.hpp"
// std
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>

namespace RType
{

SceneManager::SceneManager() {
    // initCppScriptCreators(); 
}

SceneManager::~SceneManager()
{
    // Destructor implementation
}

void SceneManager::loadScene(const std::string& sceneName, GameContext& gameContext)
{
    if (_scenes.find(sceneName) == _scenes.end())
    {
        std::cerr << "Error: Scene not found" << std::endl;
        throw std::runtime_error("Scene not found");
    }
    std::ifstream i(gameContext._assetsPath + _scenes[sceneName]);
    if (!i.is_open())
    {
        std::cerr << "Error: Could not open file" << std::endl;
        throw std::runtime_error("Could not open file");
    }
    std::cout << "Loading scene: " << sceneName << std::endl;

    nlohmann::json sceneJson;
    i >> sceneJson;
    for (const auto& entityJson : sceneJson["entities"])
    {
        mobs::Entity entity = gameContext._registry.create();
        createEntity(entityJson, entity, gameContext._registry, gameContext);
    }
}

mobs::Entity SceneManager::instantiate(const std::string& prefabName, GameContext& gameContext)
{
    auto view = gameContext._registry.view<Basics>();
    for (auto entity : view)
    {
        auto& basics = view.get<Basics>(entity);
        if (!basics.tag.compare(prefabName))
        {
            mobs::Entity newEntity = gameContext._registry.create();
            copyEntity<COMPONENT_TYPES>(
                entity, newEntity, gameContext._registry);
            return newEntity;
        }
    }
    return mobs::Entity();
}

bool SceneManager::update(GameContext& gameContext)
{
    if (_nextScene != "")
    {
        auto view = gameContext._registry.view<Basics>();
        for (auto entity : view)
        {
            auto& basics = view.get<Basics>(entity);
            if (basics.staticObject) gameContext._registry.kill(entity);
        }
        loadScene(_nextScene, gameContext);
        _currentScene = _nextScene;
        _nextScene = "";
        return true;
    }
    return false;
}

}  // namespace RType