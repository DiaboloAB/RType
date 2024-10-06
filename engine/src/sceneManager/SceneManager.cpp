/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "SceneManager.hpp"
#include <nlohmann/json.hpp>
#include "common/components.hpp"
// std
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>

namespace RType {

SceneManager::SceneManager() {
    const std::string path = "assets/scenes/";
    std::cout << "Scenes list:" << std::endl;
    for (const auto &entry : std::filesystem::directory_iterator(path)) {
        if (entry.is_regular_file()) {
            _scenesList.push_back(entry.path().filename().string());
            std::cout << entry.path().filename().string() << std::endl;
        }
    }
}

SceneManager::~SceneManager() {
    // Destructor implementation
}

void SceneManager::loadScene(const std::string &sceneName, GameContext &gameContext) {
    if (std::find(_scenesList.begin(), _scenesList.end(), sceneName) == _scenesList.end()) {
        std::cerr << "Error: Scene not found" << std::endl;
        throw std::runtime_error("Scene not found");
    }
    std::ifstream i("assets/scenes/" + sceneName);
    if (!i.is_open()) {
        std::cerr << "Error: Could not open file" << std::endl;
        throw std::runtime_error("Could not open file");
    }
    nlohmann::json sceneJson;
    i >> sceneJson;

    for (const auto& entityJson : sceneJson["entities"]) {
        mobs::Entity entity = gameContext._registry.create();
        for (const auto& componentJson : entityJson["components"].items()) {
            const std::string& componentName = componentJson.key();
            const auto& componentData = componentJson.value();

            if (componentName == "Transform") {
                gameContext._registry.emplace<Transform>(
                    entity,
                    mlg::vec3(componentData["position"][0], componentData["position"][1], componentData["position"][2])
                );
            } else if (componentName == "Sprite") {
                gameContext._registry.emplace<Sprite>(
                    entity,
                    componentData["texture"].get<std::string>()
                );
            } else if (componentName == "Scripts") {
                gameContext._registry.emplace<Scripts>(entity);
                auto& scripts = gameContext._registry.get<Scripts>(entity);
                for (const auto& script : componentData) {
                    scripts.addScript(script.get<std::string>());
                }
            }
        }
    }

}

void SceneManager::update(GameContext &gameContext) {
    if (_nextScene != "") {
        gameContext._registry.clear();
        loadScene(_nextScene, gameContext);
        _currentScene = _nextScene;
        _nextScene = "";
    }
}

}