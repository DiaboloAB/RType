/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef ISYSTEM_H
#define ISYSTEM_H

#include <gameContext/GameContext.hpp>

#include "RTypeECS.hpp"
// std

namespace RType
{

class ISystem
{
   public:
    ~ISystem() = default;

    virtual void start(ECS::Registry &registry, GameContext &gameContext) {}

    virtual void update(ECS::Registry &registry, GameContext &gameContext) {}

    virtual void draw(ECS::Registry &registry, GameContext &gameContext) {}

   private:
    // Member variables
};

}  // namespace RType

#endif  // ISYSTEM_H