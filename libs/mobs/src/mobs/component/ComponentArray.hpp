/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef COMPONENTARRAY_H
#define COMPONENTARRAY_H

#include "mobs/entity/EntityManager.hpp"

// std
#include <memory>
#include <optional>
#include <vector>

namespace mobs
{

/**
 * @class IComponentArray
 * @brief Interface for component arrays used in the RType game engine.
 */
class IComponentArray
{
   public:
    /**
     * @brief Virtual destructor for IComponentArray.
     */
    virtual ~IComponentArray() = default;

    /**
     * @brief Handles the destruction of an entity, removing its component.
     * 
     * @param entity The entity to be destroyed.
     */
    virtual void entityDestroyed(Entity entity) = 0;
};

/**
 * @class ComponentArray
 * @brief Manages an array of components for entities.
 * 
 * @tparam Component The type of the component.
 */
template <typename Component>
class ComponentArray : public IComponentArray
{
   public:
    /**
     * @brief Default constructor for ComponentArray.
     */
    ComponentArray() = default;

    /**
     * @brief Default destructor for ComponentArray.
     */
    ~ComponentArray() = default;

    /**
     * @brief Inserts a component for a specific entity.
     * 
     * @param entity The entity to insert the component for.
     * @param component The component to insert.
     */
    void insertComponent(Entity entity, Component component)
    {
        if (entity >= _components.size()) _components.resize(entity + 1);
        _components[entity] = component;
    }

    /**
     * @brief Removes a component from a specific entity.
     * 
     * @param entity The entity to remove the component from.
     */
    void removeComponent(Entity entity) { _components[entity].reset(); }

    /**
     * @brief Retrieves the component associated with a specific entity.
     * 
     * @param entity The entity whose component is to be retrieved.
     * @return Reference to the component.
     */
    Component& getComponent(Entity entity) { return _components[entity].value(); }

    /**
     * @brief Handles the destruction of an entity, removing its component.
     * 
     * @param entity The entity to be destroyed.
     */
    void entityDestroyed(Entity entity) override
    {
        if (entity >= _components.size()) return;
        if (_components[entity].has_value()) _components[entity].reset();
        _components[entity].reset();
    }

   private:
    std::vector<std::optional<Component>> _components; ///< Vector of optional components.
};

}  // namespace mobs

#endif  // COMPONENTARRAY_H