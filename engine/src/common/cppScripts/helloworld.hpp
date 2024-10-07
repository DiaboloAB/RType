/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef HELLOWORLD_H
#define HELLOWORLD_H

#include "gameContext/GameContext.hpp"
#include "cppScript/ICppScript.hpp"

namespace RType
{

class HelloWorldScript : public RType::ICppScript
{
public:
    void update(mobs::Registry &registry, GameContext &gameContext) override
    {
        if (gameContext._runtime->getKeyDown(KeyCode::H)) {
            std::cout << "Hello, World!" << std::endl;
            gameContext._sceneManager._nextScene = "scenes1.json";
        }
    }
};

}

#endif // HELLOWORLD_H