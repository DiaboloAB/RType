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

SceneManager::SceneManager()
{
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
        bool alreadyLoaded = std::find(_alreadyLoadedScenes.begin(), _alreadyLoadedScenes.end(), sceneName) != _alreadyLoadedScenes.end();
        createEntity(entityJson, entity, gameContext._registry, gameContext, alreadyLoaded);
    }
    _currentScene = sceneName;
    _alreadyLoadedScenes.push_back(sceneName);
}

mobs::Entity SceneManager::instantiate(const std::string& prefabName, GameContext& gameContext)
{
    if (_prefabs.find(prefabName) == _prefabs.end())
    {
        std::cerr << "Error: Prefab not found" << std::endl;
        throw std::runtime_error("Prefab not found");
    }
    std::ifstream i(gameContext._assetsPath + _prefabs[prefabName]);
    if (!i.is_open())
    {
        std::cerr << "Error: Could not open file" << std::endl;
        throw std::runtime_error("Could not open file");
    }
    std::cout << "Loading prefab: " << prefabName << std::endl;
    nlohmann::json prefabJson;
    i >> prefabJson;
    mobs::Entity entity = gameContext._registry.create();
    _prefabLoaded = true;
    createEntity(prefabJson, entity, gameContext._registry, gameContext);
    return entity;
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
        _nextScene = "";
        return true;
    }
    if (_prefabLoaded)
    {
        _prefabLoaded = false;
        return true;
    }
    return false;
}

void SceneManager::startEntities(mobs::Registry& registry, GameContext& gameContext)
{
    for (auto entity : _entitiesToStart) {
        if (registry.hasComponent<CppScriptComponent>(entity)) {
            auto& scripts = registry.get<CppScriptComponent>(entity);
            scripts.startAll(registry, gameContext);
        }

        if (registry.hasComponent<Scripts>(entity)) {
            auto& scripts = registry.get<Scripts>(entity);
            scripts.startAll(registry, gameContext);
        }
    }
    _entitiesToStart.clear();
}

}  // namespace RType