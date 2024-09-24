/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "RTypeEngine.hpp"

using namespace RType;

Engine::Engine()
{
    // Constructor implementation
}

Engine::~Engine()
{
    // Destructor implementation
}

struct Position
{
    float x;
    float y;

    Position(float x, float y) : x(x), y(y) {}
};

void Engine::run()
{
    ECS::Entity entity = _registry.create();
    _registry.emplace<Position>(entity, 0.0f, 0.0f);
    Position &pos = _registry.getComponent<Position>(entity);

    std::cout << "Position: " << pos.x << ", " << pos.y << std::endl;
    int i = 0;
    while (i < 10)
    {
        pos.x += 1.0f;
        pos.y += 1.0f;
        std::cout << "Position: " << pos.x << ", " << pos.y << std::endl;
        i++;
    }
    Position &pos2 = _registry.getComponent<Position>(entity);
    std::cout << "Position: " << pos2.x << ", " << pos2.y << std::endl;
}