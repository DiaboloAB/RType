/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "RTypeEngine.hpp"
#include "components/basicComponents.hpp"

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

    for (int i = 0; i < 10; i++)
    {
        ECS::Entity entity = _registry.create();
        if (i % 2 == 0)
            _registry.emplace<Position>(entity, 0.0f, i * 10.0f);
    }


    auto view = _registry.view<Position, Velocity>();
    for (auto entity : view)
    {
        Position &pos = view.get<Position>(entity);
        std::cout << "Position: " << pos.x << ", " << pos.y << std::endl;
    }

}