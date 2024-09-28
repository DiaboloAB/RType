/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef RTYPE_H
#define RTYPE_H

#include "RTypeECS.hpp"
#include "gameContext/GameContext.hpp"
#include "system/SystemManager.hpp"

// std
#include <iostream>
#include <chrono>

namespace RType
{
class Engine
{
   public:
    Engine();
    ~Engine();

    void run();
    // Getters

    // Setters

   private:
    ECS::Registry _registry;
    SystemManager _systemManager;
    GameContext _gameContext;

    // Member variables
};

}  // namespace RType

#endif  // RTYPE_H