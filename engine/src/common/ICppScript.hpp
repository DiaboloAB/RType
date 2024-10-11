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

/**
 * @class ICppScript
 * @brief Interface for C++ scripts used in the RType game engine.
 */
class ICppScript
{
public:
    /**
     * @brief Virtual destructor for ICppScript.
     */
    virtual ~ICppScript() = default;

    /**
     * @brief Called when the script starts.
     * 
     * @param registry Reference to the entity-component registry.
     * @param gameContext Reference to the game context.
     */
    virtual void start(mobs::Registry &registry, GameContext &gameContext) {}

    /**
     * @brief Called every frame to update the script.
     * 
     * @param registry Reference to the entity-component registry.
     * @param gameContext Reference to the game context.
     */
    virtual void update(mobs::Registry &registry, GameContext &gameContext) {}

    /**
     * @brief Called every frame to draw the script.
     * 
     * @param registry Reference to the entity-component registry.
     * @param gameContext Reference to the game context.
     */
    virtual void draw(mobs::Registry &registry, GameContext &gameContext) {}

    /**
     * @brief Called when a collision occurs.
     * 
     * @param registry Reference to the entity-component registry.
     * @param gameContext Reference to the game context.
     */
    virtual void onCollision(mobs::Registry &registry, GameContext &gameContext) {}

    /**
     * @brief Calls a function by name with arguments.
     * 
     * @param functionName The name of the function to call.
     * @param registry Reference to the entity-component registry.
     * @param gameContext Reference to the game context.
     * @param args The arguments to pass to the function.
     */
    virtual void callFunction(const std::string &functionName, mobs::Registry &registry,
                              GameContext &gameContext, const std::vector<std::string> &args) {}

    /**
     * @brief Sets the entity associated with this script.
     * 
     * @param entity The entity to associate with this script.
     */
    virtual void setEntity(mobs::Entity entity) = 0;

private:
    // Member variables
};

}  // namespace RType

#endif  // ICPPSCRIPT_H