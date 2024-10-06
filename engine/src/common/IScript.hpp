/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef ISCRIPT_H
#define ISCRIPT_H

#include "gameContext/GameContext.hpp"
#include "mobs/mobs.hpp"
// std
#include <iostream>

namespace RType
{

class IScript {
public:
    ~IScript() = default;

    virtual void start(mobs::Registry &registry, GameContext &gameContext) {}

    virtual void update(mobs::Registry &registry, GameContext &gameContext) {}

    virtual void draw(mobs::Registry &registry, GameContext &gameContext) {}

    virtual void onCollision(mobs::Registry &registry, GameContext &gameContext) {}

private:
    // Member variables
};

} // namespace RType

#endif // ISCRIPT_H