/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "RTypeEngine.hpp"

#include "IRuntime/NullRuntime/NullRuntime.hpp"
#include "RenderSystemSFML/RenderSystemSFML.hpp"
#include "common/systems/ColisionSystem.hpp"
#include "common/systems/CppScriptsSystem.hpp"
#include "common/systems/DrawableSystem.hpp"
#include "common/systems/HealthSystem.hpp"
#include "common/systems/NetworkSystem.hpp"
#include "common/systems/ScriptsSystem.hpp"
#include "common/systems/AudioSystem.hpp"
#include "common/systems/ScrollSystem.hpp"
#include "common/systems/SpriteSystem.hpp"
#include "common/systems/TimerSystem.hpp"
#include "common/systems/forward.hpp"

using namespace RType;

Engine::Engine()
    : _runtime((std::shared_ptr<IRuntime>)std::make_shared<RenderSystemSFML>()),
      _gameContext(_registry, _sceneManager, _runtime)
{
    std::cout << "----- Engine -----" << std::endl;

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
    _systemManager.addSystem<NetworkMoveSystem>();

    std::cout << "Engine Status: Running" << std::endl;
}

Engine::Engine(std::string host, unsigned int port, bool isServer, bool graphical)
    : _graphical(graphical),
      _runtime(_graphical ? (std::shared_ptr<IRuntime>)std::make_shared<RenderSystemSFML>()
                          : (std::shared_ptr<IRuntime>)std::make_shared<NullRuntime>()),
      _gameContext(_registry, _sceneManager, _runtime)
{
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
}

Engine::~Engine()
{
    // Destructor implementation
}

void Engine::run()
{
    _systemManager.load(_registry, _gameContext);
    _systemManager.start(_registry, _gameContext);

    _gameContext.setNetworkHandler(_networkHandler);

    _registry.kill(0);

    while (_gameContext._runtime->isWindowOpen())
    {
        _gameContext._runtime->pollEvents();
        if (_gameContext._runtime->getKey(KeyCode::Close)) break;

        if (_gameContext._runtime->getKeyDown(KeyCode::Enter) &&
            !_gameContext._networkHandler->getIsServer())
        {
            Network::HiServerPacket packet = Network::HiServerPacket();
            _gameContext._networkHandler->sendNewPacket(
                packet, _gameContext._networkHandler->getEndpointMap().begin()->first);
        }

        if (_gameContext._runtime->getKeyDown(KeyCode::P) &&
            !_gameContext._networkHandler->getIsServer())
        {
            Network::ClientEventPacket packet = Network::ClientEventPacket(Network::GAME_START);
            _gameContext._networkHandler->sendNewPacket(
                packet, _gameContext._networkHandler->getEndpointMap().begin()->first);
        }

        _clockManager.update();
        if (_sceneManager.update(_gameContext)) _systemManager.load(_registry, _gameContext);

        _gameContext._deltaT = _clockManager.getDeltaT();
        _systemManager.update(_registry, _gameContext);

        if (_clockManager.getDrawDeltaT() >= _clockManager.getTargetDrawDeltaT())
        {
            _gameContext._deltaT = _clockManager.getDrawDeltaT();

            _runtime->clearWindow();
            _systemManager.draw(_registry, _gameContext);
            _runtime->updateWindow();

            _clockManager.getDrawDeltaT() = 0.0f;
        }
    }
}
