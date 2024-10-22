/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "RTypeEngine.hpp"

#include "IRuntime/NullRuntime/NullRuntime.hpp"
#include "RenderSystemSFML/RenderSystemSFML.hpp"
#include "common/systems/AudioSystem.hpp"
#include "common/systems/ColisionSystem.hpp"
#include "common/systems/CppScriptsSystem.hpp"
#include "common/systems/DrawableSystem.hpp"
#include "common/systems/HealthSystem.hpp"
#include "common/systems/NetworkSystem.hpp"
#include "common/systems/ScriptsSystem.hpp"
#include "common/systems/ScrollSystem.hpp"
#include "common/systems/SpriteSystem.hpp"
#include "common/systems/TimerSystem.hpp"
#include "common/systems/forward.hpp"

#include <fstream>

using namespace RType;

Engine::Engine()
{
    std::cout << "----- Engine -----" << std::endl;
    std::cout << "Engine Status: Initializing" << std::endl;
    std::cout << "Engine Status: Constructing runtime" << std::endl;
    _runtime = std::make_shared<RenderSystemSFML>();
    std::cout << "Engine Status: Constructing game context" << std::endl;
    _gameContext = std::make_shared<GameContext>(_registry, _sceneManager, _runtime);
    std::cout << "Engine Status: Loading game" << std::endl;
    try {
        loadGame();
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return;
    }

    _systemManager.addSystem<ScriptSystem>();
    _systemManager.addSystem<SpriteSystem>();
    _systemManager.addSystem<ForwardSystem>();
    _systemManager.addSystem<CppScriptsSystem>();
    _systemManager.addSystem<TimerSystem>();
    _systemManager.addSystem<ColisionSystem>();
    _systemManager.addSystem<HealthSystem>();
    _systemManager.addSystem<ScrollSystem>();
    _systemManager.addSystem<NetworkSystem>();
    _systemManager.addSystem<DrawableSystem>();
    _systemManager.addSystem<AudioSystem>();

    std::cout << "Engine Status: Running" << std::endl;
}

Engine::Engine(std::string host, unsigned int port, bool isServer, bool graphical)
    : _graphical(graphical)
{
    std::cout << "----- Engine -----" << std::endl;

    _runtime = _graphical ? (std::shared_ptr<IRuntime>)std::make_shared<RenderSystemSFML>() :
        (std::shared_ptr<IRuntime>)std::make_shared<NullRuntime>();
    _gameContext = std::make_shared<GameContext>(_registry, _sceneManager, _runtime);

    this->_networkHandler = std::make_shared<Network::NetworkHandler>(host, port, isServer);
    _systemManager.addSystem<ScriptSystem>();
    _systemManager.addSystem<SpriteSystem>();
    _systemManager.addSystem<ForwardSystem>();
    _systemManager.addSystem<CppScriptsSystem>();
    _systemManager.addSystem<TimerSystem>();
    _systemManager.addSystem<ColisionSystem>();
    _systemManager.addSystem<HealthSystem>();
    _systemManager.addSystem<ScrollSystem>();
    _systemManager.addSystem<NetworkSystem>();
    _systemManager.addSystem<DrawableSystem>();
    _systemManager.addSystem<AudioSystem>();
}

Engine::~Engine()
{
    // Destructor implementation
}

void Engine::loadGame()
{
    std::ifstream i(std::string("assets/") + "game.json");
    if (!i.is_open()) throw std::runtime_error("Configuration file (assets/game.json) not found");

    i >> _gameConfig;

    std::cout << "Scenes list" << std::endl;

    std::map<std::string, std::string> scenesMap;
    if (_gameConfig.contains("scenes") && _gameConfig["scenes"].is_array()) {
        for (const auto& scene : _gameConfig["scenes"]) {
            if (scene.contains("name") && scene.contains("path")) {
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
    if (_gameConfig.contains("prefabs") && _gameConfig["prefabs"].is_array()) {
        for (const auto& prefab : _gameConfig["prefabs"]) {
            if (prefab.contains("name") && prefab.contains("path")) {
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

    _gameContext->setNetworkHandler(_networkHandler);

    while (_gameContext->_runtime->isWindowOpen())
    {
        _gameContext->_runtime->pollEvents();
        if (_gameContext->_runtime->getKey(KeyCode::Close)) break;

        if (_gameContext->_runtime->getKeyDown(KeyCode::Enter) &&
            !_gameContext->_networkHandler->getIsServer())
        {
            Network::HiServerPacket packet = Network::HiServerPacket();
            _gameContext->_networkHandler->sendNewPacket(
                packet, _gameContext->_networkHandler->getEndpointMap().begin()->first);
        }

        if (_gameContext->_runtime->getKeyDown(KeyCode::P) &&
            !_gameContext->_networkHandler->getIsServer())
        {
            Network::ClientEventPacket packet = Network::ClientEventPacket(Network::GAME_START);
            _gameContext->_networkHandler->sendNewPacket(
                packet, _gameContext->_networkHandler->getEndpointMap().begin()->first);
        }

        _clockManager.update();
        if (_sceneManager.update(*_gameContext)) _systemManager.load(_registry, *_gameContext);

        _gameContext->_deltaT = _clockManager.getDeltaT();
        _systemManager.update(_registry, *_gameContext);

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
