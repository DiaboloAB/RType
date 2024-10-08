/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef ICPPSCRIPT_H
#define ICPPSCRIPT_H

#include <memory>
#include <vector>

#include "mobs/mobs.hpp"
// std
#include <iostream>

namespace RType
{
class GameContext;

class ICppScript
{
   public:
    ~ICppScript() = default;

    virtual void start(mobs::Registry &registry, GameContext &gameContext) {}

    virtual void update(mobs::Registry &registry, GameContext &gameContext) {}

    virtual void draw(mobs::Registry &registry, GameContext &gameContext) {}

    virtual void onCollision(mobs::Registry &registry, GameContext &gameContext) {}

    virtual void callFunction(const std::string &functionName, mobs::Registry &registry,
                              GameContext &gameContext, const std::vector<std::string> &args)
    {
    }

    virtual void setEntity(mobs::Entity entity) = 0;

   private:
    // Member variables
};

}  // namespace RType

#endif  // ICPPSCRIPT_H