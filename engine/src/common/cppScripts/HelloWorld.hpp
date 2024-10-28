/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef HELLOWORLD_H
#define HELLOWORLD_H

#include "common/ICppScript.hpp"
#include "gameContext/GameContext.hpp"
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
        if (gameContext._runtime->getKeyDown(KeyCode::Space))
            gameContext._sceneManager.loadPrefab("HelloWorld");
    }

    static constexpr const char *name = "HelloWorld";

private:
    // Member variables
};

} // namespace RType

#endif // HELLOWORLD_H