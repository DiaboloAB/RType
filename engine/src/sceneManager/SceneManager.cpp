/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "SceneManager.hpp"

#include "common/components.hpp"
#include "common/cppScripts/AnimPlayer.hpp"
#include "common/cppScripts/AnimThruster.hpp"
#include "common/cppScripts/EnemyFactory.hpp"
#include "common/cppScripts/Laser.hpp"
#include "common/cppScripts/MovePlayer.hpp"
#include "common/cppScripts/MoveThruster.hpp"
#include "common/cppScripts/PlayerShoot.hpp"
#include "common/cppScripts/RedShipScript.hpp"
#include "common/cppScripts/helloworld.hpp"
#include "common/scriptsComponent.hpp"
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
    const std::string path = "assets/scenes/";
    std::cout << "Scenes list:" << std::endl;
    for (const auto& entry : std::filesystem::directory_iterator(path))
    {
        if (entry.is_regular_file())
        {
            _scenesList.push_back(entry.path().filename().string());
            std::cout << entry.path().filename().string() << std::endl;
        }
    }

    const std::string prefabPath = "assets/scenes/prefabs/";
    std::cout << "Prefabs list:" << std::endl;
    for (const auto& entry : std::filesystem::directory_iterator(prefabPath))
    {
        if (entry.is_regular_file())
        {
            _prefabsList.push_back(entry.path().filename().string());
            std::cout << entry.path().filename().string() << std::endl;
        }
    }

    initComponentCreators();
    initCppScriptCreators();
}

SceneManager::~SceneManager()
{
    // Destructor implementation
}

void SceneManager::loadScene(const std::string& sceneName, GameContext& gameContext)
{
    if (std::find(_scenesList.begin(), _scenesList.end(), sceneName) == _scenesList.end())
    {
        std::cerr << "Error: Scene not found" << std::endl;
        throw std::runtime_error("Scene not found");
    }
    std::ifstream i("assets/scenes/" + sceneName);
    if (!i.is_open())
    {
        std::cerr << "Error: Could not open file" << std::endl;
        throw std::runtime_error("Could not open file");
    }
    nlohmann::json sceneJson;
    i >> sceneJson;

    for (const auto& entityJson : sceneJson["entities"])
    {
        mobs::Entity entity = gameContext._registry.create();

        createEntity(entityJson, entity, gameContext._registry, gameContext);
    }
}

mobs::Entity SceneManager::loadPrefab(const std::string& prefabName, GameContext& gameContext)
{
    if (std::find(_prefabsList.begin(), _prefabsList.end(), prefabName) == _prefabsList.end())
    {
        std::cerr << "Error: Prefab not found" << std::endl;
        throw std::runtime_error("Prefab not found");
    }
    std::ifstream i("assets/scenes/prefabs/" + prefabName);
    if (!i.is_open())
    {
        std::cerr << "Error: Could not open file" << std::endl;
        throw std::runtime_error("Could not open file");
    }
    nlohmann::json prefabJson;
    i >> prefabJson;

    mobs::Entity entity = gameContext._registry.create();

    createEntity(prefabJson, entity, gameContext._registry, gameContext);
    return entity;
}

void SceneManager::update(GameContext& gameContext)
{
    if (_nextScene != "")
    {
        // gameContext._registry.clear();
        auto view = gameContext._registry.view<Basics>();
        for (auto entity : view)
        {
            auto& basics = view.get<Basics>(entity);
            if (!basics.staticObject) gameContext._registry.kill(entity);
        }
        loadScene(_nextScene, gameContext);
        _currentScene = _nextScene;
        _nextScene = "";
    }
}

}  // namespace RType