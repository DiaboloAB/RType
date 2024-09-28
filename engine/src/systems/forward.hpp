/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef FORWARD_H
#define FORWARD_H

// std

#include <components/basicComponents.hpp>
#include <system/ISystem.hpp>

namespace RType
{

class ForwardSystem : public ISystem
{
public:
    ForwardSystem() {}
    ~ForwardSystem() {}

    void update(ECS::Registry &registry, GameContext &gameContext) override {
        float deltaTime = gameContext._deltaT;
        auto view = registry.view<Position, Velocity>();
        for (auto entity : view) {
            Position &pos = view.get<Position>(entity);
            Velocity &vel = view.get<Velocity>(entity);
            pos.x += vel.x * deltaTime;
            pos.y += vel.y * deltaTime;
            std::cout << "Entity(" << entity << ") position: " << pos.x << ", " << pos.y << std::endl;
        }
    }

};


}


#endif // FORWARD_H