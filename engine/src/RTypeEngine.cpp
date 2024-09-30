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
    // Constructor implementation
}

Engine::~Engine()
{
    // Destructor implementation
}

void Engine::run()
{
    ECS::Entity entity = _registry.create();
    _registry.emplace<Transform>(entity);
    _registry.emplace<Sprite>(entity, "player");
    // _registry.emplace<Velocity>(entity, 1.0f, 1.0f);

    _systemManager.addSystem<ForwardSystem>();
    _systemManager.addSystem<SpriteSystem>();

    _gameContext._runtime->loadSprite("player", "player", "player.png");

    _systemManager.start(_registry, _gameContext);

    RenderSystemSFML renderSystem;

    if (renderSystem.loadSound("explosion", "assets/sounds/explosion.wav")) {
        std::cout << "Son 'explosion' préchargé avec succès." << std::endl;
    }
    if (renderSystem.loadSound("shoot", "shoot.ogg")) {
        std::cout << "Son 'shoot' préchargé avec succès." << std::endl;
    }

    // Jouer un son après préchargement
    std::cout << "Appuyez sur une touche pour jouer le son 'explosion'..." << std::endl;
    std::cin.get();  // Attend une entrée de l'utilisateur pour continuer
    renderSystem.playSound("explosion");

    // Jouer un autre son
    std::cout << "Appuyez sur une touche pour jouer le son 'shoot'..." << std::endl;
    std::cin.get();
    renderSystem.playSound("shoot");

    // Décharger un son du cache
    std::cout << "Déchargement du son 'shoot'..." << std::endl;
    renderSystem.unloadSound("shoot");

    // Tester le fait de rejouer un son déchargé
    std::cout << "Appuyez sur une touche pour essayer de rejouer le son 'shoot' après déchargement..." << std::endl;
    std::cin.get();
    renderSystem.playSound("shoot");
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