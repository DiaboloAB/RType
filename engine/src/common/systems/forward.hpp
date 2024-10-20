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

    void update(mobs::Registry &registry, GameContext &gameContext) override
    {
        float deltaTime = gameContext._deltaT;
        auto view = registry.view<Transform>();
        return;
        for (auto entity : view)
        {
            auto &transform = view.get<Transform>(entity);
            int speed = 1000;
            if (gameContext._runtime->getKey(KeyCode::UpArrow))
            {
                transform.position.y -= speed * deltaTime;
            }
            if (gameContext._runtime->getKey(KeyCode::DownArrow))
            {
                transform.position.y += speed * deltaTime;
            }
            if (gameContext._runtime->getKey(KeyCode::LeftArrow))
            {
                transform.position.x -= speed * deltaTime;
            }
            if (gameContext._runtime->getKey(KeyCode::RightArrow))
            {
                transform.position.x += speed * deltaTime;
            }
            if (gameContext._runtime->getKeyDown(KeyCode::Space))
            {
                gameContext._sceneManager._nextScene = "scenes1.json";
            }
            if (gameContext._runtime->getKeyDown(KeyCode::H))
            {
                std::cout << "Hello World" << std::endl;
            }
        }
    }
};

}  // namespace RType

#endif  // FORWARD_H