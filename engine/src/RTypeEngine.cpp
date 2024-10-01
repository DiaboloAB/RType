/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "RTypeEngine.hpp"
#include "common/systems/forward.hpp"
#include "common/systems/SpriteSystem.hpp"
#include "RenderSystemSFML/RenderSystemSFML.hpp"

using namespace RType;

Engine::Engine()
{
    // Demarer l'intrerface graphique
    // Recup l'host du server et son port
    // Init le NetworkHandler du client (std::make_shared<Network::NetworkHandler>(host, port, false);)
}

Engine::Engine(std::string host, unsigned int port, bool isServer)
{
    std::cout << "................" << std::endl;
    this->_networkHandler = std::make_shared<Network::NetworkHandler>(host, port, isServer);
    std::cout << "................" << std::endl;
}

Engine::~Engine()
{
    // Destructor implementation
}

void Engine::run()
{
    if (this->_networkHandler != nullptr && this->_networkHandler->getIsServer() == false) {

        std::cout << "SERVER IN IF" << std::endl;
        ECS::Entity entity = _registry.create();
        _registry.emplace<Transform>(entity);
        _registry.emplace<Sprite>(entity, "player.png");
        // _registry.emplace<Velocity>(entity, 1.0f, 1.0f);

        _systemManager.addSystem<ForwardSystem>();
        _systemManager.addSystem<SpriteSystem>();

        _gameContext._runtime->loadSprite("player", "player", "player.png");

        _systemManager.start(_registry, _gameContext);
        while (_gameContext._runtime->isWindowOpen())
        {
            _gameContext._runtime->pollEvents();
            _gameContext.update();

            if (_gameContext._runtime->getKey(KeyCode::Close))
                break;


            _systemManager.update(_registry, _gameContext);

            _gameContext._runtime->clearWindow();
            _systemManager.draw(_registry, _gameContext);
            // _gameContext._runtime->drawSprite("player", 50, 50);
            _gameContext._runtime->updateWindow();
        }
    }
    std::cout << "SERVER NOT IN IF" << std::endl;

}