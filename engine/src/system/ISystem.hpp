/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef ISYSTEM_H
#define ISYSTEM_H

#include <gameContext/GameContext.hpp>

#include "mobs/mobs.hpp"
// std

namespace RType
{

/**
 * @class ISystem
 * @brief Interface for systems used in the RType game engine.
 */
class ISystem
{
   public:
    /**
     * @brief Virtual destructor for ISystem.
     */
    ~ISystem() = default;

    /**
     * @brief Called when the system starts.
     *
     * @param registry Reference to the entity-component registry.
     * @param gameContext Reference to the game context.
     */
    virtual void start(mobs::Registry &registry, GameContext &gameContext) {}

    /**
     * @brief Called when a new object or scene is loaded.
     *
     * @param registry Reference to the entity-component registry.
     * @param gameContext Reference to the game context.
     */
    virtual void load(mobs::Registry &registry, GameContext &gameContext) {}

    /**
     * @brief Called when the system stops.
     *
     * @param registry Reference to the entity-component registry.
     * @param gameContext Reference to the game context.
     */
    virtual void stop(mobs::Registry &registry, GameContext &gameContext) {}

    /**
     * @brief Called every frame to update the system.
     *
     * @param registry Reference to the entity-component registry.
     * @param gameContext Reference to the game context.
     */
    virtual void update(mobs::Registry &registry, GameContext &gameContext) {}

    /**
     * @brief Called every frame to draw the system.
     *
     * @param registry Reference to the entity-component registry.
     * @param gameContext Reference to the game context.
     */
    virtual void draw(mobs::Registry &registry, GameContext &gameContext) {}

   private:
    // Member variables
};

}  // namespace RType

#endif  // ISYSTEM_H