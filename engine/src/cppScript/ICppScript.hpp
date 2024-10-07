/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef ICPPSCRIPT_H
#define ICPPSCRIPT_H

#include "mobs/mobs.hpp"
#include <memory>
#include <vector>
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

    virtual void callFunction(const std::string &functionName,
        mobs::Registry &registry, GameContext &gameContext,
                              const std::vector<std::string> &args) {}

   private:
    // Member variables
};

struct CppScriptComponent
{
    std::vector<std::unique_ptr<ICppScript>> scripts;

    void addScript(std::unique_ptr<ICppScript> script)
    {
        scripts.push_back(std::move(script));
    }
};

}  // namespace RType

#endif  // ICPPSCRIPT_H