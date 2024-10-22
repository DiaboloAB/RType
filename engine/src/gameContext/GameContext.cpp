/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "GameContext.hpp"

#include "RenderSystemSFML/RenderSystemSFML.hpp"
// std
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using namespace RType;

GameContext::GameContext(mobs::Registry &registry, SceneManager &sceneManager,
                         std::shared_ptr<IRuntime> runtime)
    : _runtime(runtime), _registry(registry), _sceneManager(sceneManager)
{
    std::cout << "----- Game context -----" << std::endl;

    std::ifstream i("assets/game.json");

    if (!i.is_open())
    {
        std::cerr << "Error: Could not open file" << std::endl;
        throw std::runtime_error("Could not open file");
    }
    nlohmann::json j;
    i >> j;

    std::cout << "Scenes list" << std::endl;

    std::map<std::string, std::string> scenesMap;
    if (j.contains("scenes") && j["scenes"].is_array()) {
        for (const auto& scene : j["scenes"]) {
            if (scene.contains("name") && scene.contains("path")) {
                std::string name = scene["name"];
                std::string path = scene["path"];
                scenesMap[name] = path;
                std::cout << "\t- " << name << " : " << path << std::endl;
            }
        }
    }
    sceneManager.setScenes(scenesMap);

    std::cout << "Prefab list" << std::endl;
    std::map<std::string, std::string> prefabsMap;
    if (j.contains("prefabs") && j["prefabs"].is_array()) {
        for (const auto& prefab : j["prefabs"]) {
            if (prefab.contains("name") && prefab.contains("path")) {
                std::string name = prefab["name"];
                std::string path = prefab["path"];
                prefabsMap[name] = path;
                std::cout << "\t- " << name << " : " << path << std::endl;
            }
        }
    }

    std::string defaultScene = j["defaultScene"];
    std::cout << "Default scene: " << defaultScene << std::endl;
    _sceneManager.loadScene(defaultScene, *this);

    // std::cout << "Font list" << std::endl;
    // try
    // {
    //     std::vector<std::string> fontList = j["fontList"];
    //     for (const auto &font : fontList)
    //     {
    //         _runtime->loadFont(font);
    //         std::cout << "\t- " << font << std::endl;
    //     }
    // }
    // catch (const std::exception &e)
    // {
    //     std::cerr << "Error: " << e.what() << std::endl;
    // }
    this->_networkHandler = nullptr;
}

GameContext::~GameContext()
{
    // Destructor implementation
}
