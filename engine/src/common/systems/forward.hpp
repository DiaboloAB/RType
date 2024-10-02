/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef FORWARD_H
#define FORWARD_H

// std

#include <common/components.hpp>
#include <system/ISystem.hpp>

namespace RType
{

class ForwardSystem : public ISystem
{
   public:
    ForwardSystem() {}
    ~ForwardSystem() {}

    void update(ECS::Registry &registry, GameContext &gameContext) override
    {
        float deltaTime = gameContext._deltaT;
        auto view = registry.view<Transform>();

        for (auto entity : view)
        {
            auto &transform = view.get<Transform>(entity);
            int speed = 1000;
            if (gameContext._runtime->getKey(KeyCode::UpArrow))
            {
                transform.position.y -= speed * deltaTime;
                std::cout << "Moving up" << std::endl;
            }
            if (gameContext._runtime->getKey(KeyCode::DownArrow))
            {
                transform.position.y += speed * deltaTime;
                std::cout << "Moving down" << std::endl;
            }
            if (gameContext._runtime->getKey(KeyCode::LeftArrow))
            {
                transform.position.x -= speed * deltaTime;
                std::cout << "Moving left" << std::endl;
            }
            if (gameContext._runtime->getKey(KeyCode::RightArrow))
            {
                transform.position.x += speed * deltaTime;
                std::cout << "Moving right" << std::endl;
            }
        }
    }
};

}  // namespace RType

#endif  // FORWARD_H