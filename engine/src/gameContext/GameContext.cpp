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
    std::ifstream i("assets/game.json");

    if (!i.is_open())
    {
        std::cerr << "Error: Could not open file" << std::endl;
        throw std::runtime_error("Could not open file");
    }
    nlohmann::json j;
    i >> j;

    std::string defaultScene = j["defaultScene"];
    std::cout << "Default scene: " << defaultScene << std::endl;
    _sceneManager.loadScene(defaultScene, *this);

    try
    {
        std::vector<std::string> fontList = j["fontList"];
        for (const auto &font : fontList)
        {
            _runtime->loadFont(font);
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    this->_networkHandler = nullptr;
}

GameContext::~GameContext()
{
    // Destructor implementation
}
