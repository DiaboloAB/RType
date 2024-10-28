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
#include <map>
#include <string>
#include <functional>
#include <iostream>
#include <memory>

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
     * @brief Called when a collision occurs.
     *
     * @param registry Reference to the entity-component registry.
     * @param gameContext Reference to the game context.
     */
    virtual void onCollision(mobs::Registry &registry, GameContext &gameContext, mobs::Entity other) {}


     /**
     * @brief Sets the entity associated with this script.
     *
     * @param entity The entity to associate with this script.
     */
    void setEntity(mobs::Entity entity) { m_entity = entity; }

    /**
     * @brief Gets the entity associated with this script.
     *
     * @return The entity associated with this script.
     */
    mobs::Entity getEntity() const { return m_entity; }

   private:
    mobs::Entity m_entity;
};

}  // namespace RType

#endif  // ICPPSCRIPT_H