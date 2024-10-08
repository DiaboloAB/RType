/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "SceneManager.hpp"

#include "common/components.hpp"
#include "common/cppScripts/changeAnim.hpp"
#include "common/cppScripts/helloworld.hpp"
#include "common/cppScripts/MovePlayer.hpp"
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

void SceneManager::loadPrefab(const std::string& prefabName, GameContext& gameContext)
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
            const std::string& componentName = componentJson.key();
            const auto& componentData = componentJson.value();

            if (componentName == "Transform")
            {
                registry.emplace<Transform>(
                    entity, mlg::vec3(componentData["position"][0], componentData["position"][1],
                                      componentData["position"][2]));
            }
            else if (componentName == "Sprite")
            {
                registry.emplace<Sprite>(entity, componentData["texture"].get<std::string>());
            }
            else if (componentName == "Scripts")
            {
                registry.emplace<Scripts>(entity);
                auto& scripts = registry.get<Scripts>(entity);
                for (const auto& script : componentData)
                {
                    scripts.addScript(script.get<std::string>(), gameContext);
                }
            }
            else if (componentName == "CppScripts")
            {
                std::cout << "CppScripts" << std::endl;
                registry.emplace<CppScriptComponent>(entity, entity);
                auto& scripts = registry.get<CppScriptComponent>(entity);
                for (const auto& script : componentData)
                {
                    if (script.get<std::string>() == "HelloWorld")
                    {
                        scripts.addScript(std::make_shared<HelloWorldScript>());
                    }
                    else if (script.get<std::string>() == "ChangeAnim")
                    {
                        scripts.addScript(std::make_shared<ChangeAnimScript>());
                    }
                    else if (script.get<std::string>() == "MovePlayer")
                    {
                        scripts.addScript(std::make_shared<MovePlayerScript>());
                    }
                }
            }
            else if (componentName == "Network")
            {
                registry.emplace<NetworkComp>(entity, componentData["id"],
                                              componentData["authority"].get<std::string>());
            }
            else if (componentName == "Animator")
            {
                registry.emplace<Animator>(entity);
                auto& animator = registry.get<Animator>(entity);
                for (const auto& animation : componentData)
                {
                    animator.animations.addAnimation(Animation(
                        animation["texture"].get<std::string>(), animation["frameCount"].get<int>(),
                        animation["speed"].get<float>(),
                        mlg::vec2(animation["frameSize"][0], animation["frameSize"][1], 0),
                        mlg::vec2(animation["scale"][0], animation["scale"][1], 0),
                        animation["rotation"].get<float>(), animation["name"].get<std::string>(),
                        animation["loop"].get<bool>()));
                }
            }
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: Could not create entity" << std::endl;
    }
}

}  // namespace RType