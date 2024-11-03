/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef HELLOWORLD_H
#define HELLOWORLD_H

#include "common/COMPONENTLIST.hpp"
#include "common/ICppScript.hpp"
#include "gameContext/GameContext.hpp"
// std

using namespace RType;

class HelloWorld : public ICppScript
{
   public:
    HelloWorld() {}
    ~HelloWorld() {}

    void update(mobs::Registry &registry, GameContext &gameContext) override
    {
        if (gameContext._runtime->getKey(KeyCode::UpArrow))
        {
            registry.get<Transform>(getEntity()).position.y -= 1;
        }
        if (gameContext._runtime->getKey(KeyCode::DownArrow))
        {
            registry.get<Transform>(getEntity()).position.y += 1;
        }
        if (gameContext._runtime->getKey(KeyCode::LeftArrow))
        {
            registry.get<Transform>(getEntity()).position.x -= 1;
        }
        if (gameContext._runtime->getKey(KeyCode::RightArrow))
        {
            registry.get<Transform>(getEntity()).position.x += 1;
        }
    }

    void onCollisionStay(mobs::Registry &registry, GameContext &gameContext,
                         mobs::Entity other) override
    {
    }
    void onCollisionEnter(mobs::Registry &registry, GameContext &gameContext,
                          mobs::Entity other) override
    {
        std::cout << "collide enter with " << other << std::endl;
    }

    void onCollisionExit(mobs::Registry &registry, GameContext &gameContext,
                         mobs::Entity other) override
    {
        std::cout << "collide exit with " << other << std::endl;
    }
    static constexpr const char *name = "HelloWorld";

   private:
    // Member variables
};

#endif  // HELLOWORLD_H