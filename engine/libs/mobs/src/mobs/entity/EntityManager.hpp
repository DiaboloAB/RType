/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

// std
#include <array>
#include <bitset>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <iterator>
#include <queue>
#include <vector>

namespace mobs
{

using Entity = std::uint32_t;      ///< Type alias for entity identifier.
const Entity MAX_ENTITIES = 5000;  ///< The maximum number of entities.

using ComponentType = std::uint8_t;             ///< Type alias for component type.
const ComponentType MAX_COMPONENTS = 32;        ///< The maximum number of components.
using Signature = std::bitset<MAX_COMPONENTS>;  ///< Type alias for entity signature.

/**
 * @class EntityManager
 * @brief Manages the creation, destruction, and signature of entities.
 */
class EntityManager
{
   public:
    /**
     * @brief Constructs a new EntityManager object.
     */
    EntityManager();

    /**
     * @brief Destroys the EntityManager object.
     */
    ~EntityManager();

    /**
     * @brief Creates a new entity.
     *
     * @return The created entity.
     */
    Entity create();

    /**
     * @brief Kills an entity, removing it from the registry.
     *
     * @param entity The entity to kill.
     */
    void kill(Entity entity);

    /**
     * @brief Clears all entities.
     */
    void clear();

    /**
     * @brief Retrieves the signature of a specific entity.
     *
     * @param entity The entity whose signature is to be retrieved.
     * @return The signature of the entity.
     */
    Signature getSignature(Entity entity);

    /**
     * @brief Gets the number of living entities.
     *
     * @return The number of living entities.
     */
    int getNbLivingEntity() { return _nbLivingEntity; }

    /**
     * @brief Sets the signature of a specific entity.
     *
     * @param entity The entity whose signature is to be set.
     * @param signature The signature to set.
     */
    void setSignature(Entity entity, Signature signature);

    /**
     * @brief Returns an iterator to the beginning of the entities vector.
     *
     * @return Iterator to the beginning of the entities vector.
     */
    std::vector<Entity>::iterator begin() { return _entities.begin(); }

    /**
     * @brief Returns an iterator to the end of the entities vector.
     *
     * @return Iterator to the end of the entities vector.
     */
    std::vector<Entity>::iterator end() { return _entities.end(); }

   private:
    std::vector<Entity> _entities;                    ///< Vector of entities.
    std::queue<Entity> _availableEntities;            ///< Queue of available entities.
    std::array<Signature, MAX_ENTITIES> _signatures;  ///< Array of entity signatures.
    int _nbLivingEntity = 0;                          ///< Number of living entities.
};

}  // namespace mobs

#endif  // ENTITYMANAGER_H