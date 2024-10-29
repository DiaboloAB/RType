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
#include "utils/random.hpp"
// std

namespace RType
{

class HelloWorld : public ICppScript
{
   public:
    HelloWorld() {}
    ~HelloWorld() {}

    void update(mobs::Registry &registry, GameContext &gameContext) override
    {
        mobs::Entity entity;
        if (gameContext._runtime->getKeyDown(KeyCode::Space))
        {
            entity = gameContext._sceneManager.instantiate("HelloWorld", gameContext);
            Transform &transform = registry.get<Transform>(entity);
            transform.position.x = random(0, 800);
            transform.position.y = random(0, 600);
        }
    }

    static constexpr const char *name = "HelloWorld";

   private:
    // Member variables
};

}  // namespace RType

#endif  // HELLOWORLD_H