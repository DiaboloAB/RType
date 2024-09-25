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

struct Velocity
{
    float x;
    float y;

    Velocity(float x, float y) : x(x), y(y) {}
};

void Engine::run() {
    // Créer des entités
    ECS::Entity entity = _registry.create();
    _registry.emplace<Position>(entity, 0.0f, 1.0f);
    _registry.emplace<Velocity>(entity, 1.0f, 1.0f);

    // Boucle pour créer plusieurs entités
    for (int i = 0; i < 10; i++) {
        ECS::Entity entity = _registry.create();
        if (i % 2 == 0) {
            _registry.emplace<Position>(entity, 0.0f, i * 10.0f);
        }
    }

    // Affichage des positions initiales
    auto view = _registry.view<Position>();
    for (auto entity : view) {
        Position &pos = view.get<Position>(entity);
        std::cout << "Position: " << pos.x << ", " << pos.y << std::endl;
    }
}