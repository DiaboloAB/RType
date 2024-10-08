/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "RTypeEngine.hpp"

#include "RenderSystemSFML/RenderSystemSFML.hpp"
#include "common/systems/CppScriptsSystem.hpp"
#include "common/systems/ScriptsSystem.hpp"
#include "common/systems/SpriteSystem.hpp"
#include "common/systems/forward.hpp"
#include "common/systems/NetworkSystem.hpp"

using namespace RType;

Engine::Engine() : _gameContext(_registry, _sceneManager)
{
    _systemManager.addSystem<ScriptSystem>();
    _systemManager.addSystem<SpriteSystem>();
    _systemManager.addSystem<ForwardSystem>();
    _systemManager.addSystem<CppScriptsSystem>();
    _systemManager.addSystem<NetworkSystem>();
}

Engine::Engine(std::string host, unsigned int port, bool isServer)
    : _gameContext(_registry, _sceneManager)
{
    this->_networkHandler = std::make_shared<Network::NetworkHandler>(host, port, isServer);
    this->_isServer = isServer;
    _systemManager.addSystem<ForwardSystem>();
    _systemManager.addSystem<SpriteSystem>();
    _systemManager.addSystem<ScriptSystem>();
    _systemManager.addSystem<NetworkSystem>();
}

Engine::~Engine()
{
    // Destructor implementation
}

void Engine::run()
{
    _systemManager.start(_registry, _gameContext);

    _gameContext.setNetworkHandler(_networkHandler);

    while (_gameContext._runtime->isWindowOpen())
    {
        _gameContext._runtime->pollEvents();
        _gameContext.update();

        if (_gameContext._runtime->getKey(KeyCode::Close)) break;

        _systemManager.update(_registry, _gameContext);

        _gameContext._runtime->clearWindow();
        _systemManager.draw(_registry, _gameContext);
        _gameContext._runtime->updateWindow();
    }
}

void Engine::runServer()
{
    // Server server(this->_networkHandler->getHost(), this->_networkHandler->getPort());
    // server.run();
    _systemManager.start(_registry, _gameContext);

    _gameContext.setNetworkHandler(_networkHandler);

    while (true)
    {
        _gameContext.update();

        _systemManager.update(_registry, _gameContext);
    }
}