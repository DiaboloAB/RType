/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "RTypeEngine.hpp"
#include "components/basicComponents.hpp"
#include "systems/forward.hpp"

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
    _registry.emplace<Position>(entity, 0.0f, 1.0f);
    _registry.emplace<Velocity>(entity, 1.0f, 1.0f);

    int i = 0;

    _systemManager.addSystem<ForwardSystem>();

    for (int i = 0; i < 10; i++) // replace with while (window.isOpen())
    {
        _gameContext.update();

        _systemManager.update(_registry, _gameContext);
    }

}