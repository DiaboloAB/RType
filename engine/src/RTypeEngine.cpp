/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "RTypeEngine.hpp"

#include "NullRuntime/NullRuntime.hpp"
#include "utils/getBinaryPath.hpp"

#ifdef GRAPHICS_SFML
#include "sfml_lib/RenderSystemSFML.hpp"
#elif defined(GRAPHICS_SDL)
#include "sdl_lib/RenderSystemSDL.hpp"
#endif

// std
#include <fstream>

using namespace RType;

Engine::Engine(std::map<std::string, std::string> args) : _args(args)
{
    std::cout << "----- Engine -----" << std::endl;
    _assetsPath = getAssetsPath();
    std::cout << "Assets path: " << _assetsPath << std::endl;
    std::cout << "Engine Status: Initializing" << std::endl;
    std::cout << "Engine Status: Constructing runtime" << std::endl;

    if (args.find("graphics") != args.end() && args["graphics"] == "off")
    {
        _runtime = std::make_shared<NullRuntime>();
        std::cout << "No graphics library selected!" << std::endl;
    }
    else
    {
#ifdef GRAPHICS_SFML
        _runtime = std::make_shared<RenderSystemSFML>();
        std::cout << "SFML graphics library selected!" << std::endl;
#elif defined(GRAPHICS_SDL)
        _runtime = std::make_shared<RenderSystemSDL>();
        std::cout << "SDL graphics library selected!" << std::endl;
#else
        _runtime = std::make_shared<NullRuntime>();
        std::cout << "No graphics library selected!" << std::endl;
#endif
    }

    std::cout << "Engine Status: Constructing game context" << std::endl;
    _gameContext = std::make_shared<GameContext>(_assetsPath, _registry, _sceneManager, _runtime);
    std::cout << "Engine Status: Loading game" << std::endl;

    try
    {
        loadGame();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return;
    }

    addSystems();

    std::cout << "Engine Status: Running" << std::endl;
}

Engine::~Engine()
{
    // Destructor implementation
}

void Engine::loadGame()
{
    std::ifstream i(_assetsPath + "game.json");
    if (!i.is_open()) throw std::runtime_error("Configuration file (assets/game.json) not found");

    i >> _gameConfig;

    std::cout << "Scenes list" << std::endl;

    std::map<std::string, std::string> scenesMap;
    if (_gameConfig.contains("scenes") && _gameConfig["scenes"].is_array())
    {
        for (const auto& scene : _gameConfig["scenes"])
        {
            if (scene.contains("name") && scene.contains("path"))
            {
                std::string name = scene["name"];
                std::string path = scene["path"];
                scenesMap[name] = path;
                std::cout << "\t- \"" << name << "\" : " << path << std::endl;
            }
        }
    }
    _sceneManager.setScenes(scenesMap);

    std::cout << "Prefab list" << std::endl;

    std::map<std::string, std::string> prefabsMap;
    if (_gameConfig.contains("prefabs") && _gameConfig["prefabs"].is_array())
    {
        for (const auto& prefab : _gameConfig["prefabs"])
        {
            if (prefab.contains("name") && prefab.contains("path"))
            {
                std::string name = prefab["name"];
                std::string path = prefab["path"];
                prefabsMap[name] = path;
                std::cout << "\t- \"" << name << "\" : " << path << std::endl;
            }
        }
    }
    _sceneManager.setPrefabs(prefabsMap);

    std::cout << "Default scene: " << _gameConfig["defaultScene"] << std::endl;
    _sceneManager.loadScene(_gameConfig["defaultScene"], *_gameContext);
}

void Engine::run()
{
    _systemManager.load(_registry, *_gameContext);
    _systemManager.start(_registry, *_gameContext);
    while (_gameContext->_runtime->isWindowOpen() && _gameContext->_running && !_stop)
    {
        _clockManager.update();
        if (_sceneManager.update(*_gameContext)) _systemManager.load(_registry, *_gameContext);

        _gameContext->_deltaT = _clockManager.getDeltaT();
        if (_clockManager.getUpdateDeltaT() >= _clockManager.getTargetUpdateDeltaT())
        {
            _gameContext->_runtime->pollEvents();
            if (_gameContext->_runtime->getKey(KeyCode::Close)) break;
            _systemManager.update(_registry, *_gameContext);
            _clockManager.getUpdateDeltaT() = 0.0f;
        }
        if (_clockManager.getDrawDeltaT() >= _clockManager.getTargetDrawDeltaT())
        {
            _gameContext->_deltaT = _clockManager.getDrawDeltaT();

            _runtime->clearWindow();
            _systemManager.draw(_registry, *_gameContext);
            _runtime->updateWindow();

            _clockManager.getDrawDeltaT() = 0.0f;
        }
    }
}

void Engine::stop()
{
    std::lock_guard<std::mutex> lock(this->_stopmtx);
    this->_stop = true;
}

