/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include <typeindex>
#include <unordered_map>

#include "ComponentArray.hpp"

namespace mobs
{

/**
 * @class ComponentManager
 * @brief Manages the registration and retrieval of component types and arrays.
 */
class ComponentManager
{
   public:
    /**
     * @brief Constructs a new ComponentManager object.
     */
    ComponentManager();

    /**
     * @brief Destroys the ComponentManager object.
     */
    ~ComponentManager();

    /**
     * @brief Registers a component type.
     *
     * @tparam Component The type of the component to register.
     */
    template <typename Component>
    void registerComponent()
    {
        const std::type_index typeIndex(typeid(Component));
        _componentTypes[typeIndex] = _nextComponentType++;
        _componentArrays[typeIndex] = std::make_shared<ComponentArray<Component>>();
    }

    /**
     * @brief Retrieves the component type identifier for a specific component.
     *
     * @tparam Component The type of the component.
     * @return The component type identifier.
     */
    template <typename Component>
    ComponentType getComponentType()
    {
        const std::type_index typeIndex(typeid(Component));

        if (_componentTypes.find(typeIndex) == _componentTypes.end())
        {
            return 255;
        }

        return _componentTypes[typeIndex];
    }

    /**
     * @brief Retrieves the component array for a specific component type.
     *
     * @tparam Component The type of the component.
     * @return Shared pointer to the component array.
     */
    template <typename Component>
    std::shared_ptr<ComponentArray<Component>> getComponentArray()
    {
        const std::type_index typeIndex(typeid(Component));
        return std::static_pointer_cast<ComponentArray<Component>>(_componentArrays[typeIndex]);
    }

    /**
     * @brief Adds a component to an entity.
     *
     * @tparam Component The type of the component to add.
     * @param entity The entity to add the component to.
     * @param component The component to add.
     */
    template <typename Component>
    void addComponent(Entity entity, Component component)
    {
        getComponentArray<Component>()->insertComponent(entity, component);
    }

    /**
     * @brief Removes a component from an entity.
     *
     * @tparam Component The type of the component to remove.
     * @param entity The entity to remove the component from.
     */
    template <typename Component>
    void removeComponent(Entity entity)
    {
        getComponentArray<Component>()->removeComponent(entity);
    }

    /**
     * @brief Retrieves a component of a specific entity.
     *
     * @tparam Component The type of the component to retrieve.
     * @param entity The entity whose component is to be retrieved.
     * @return Reference to the component.
     */
    template <typename Component>
    Component& getComponent(Entity entity)
    {
        return getComponentArray<Component>()->getComponent(entity);
    }

    /**
     * @brief Destroys an entity.
     *
     * @param entity The entity to destroy.
     */
    void entityDestroyed(Entity entity)
    {
        for (auto const& pair : _componentArrays)
        {
            auto const& component = pair.second;
            component->entityDestroyed(entity);
        }
    }

   private:
    std::unordered_map<std::type_index, ComponentType>
        _componentTypes;  ///< Map of component types.
    std::unordered_map<std::type_index, std::shared_ptr<IComponentArray>>
        _componentArrays;                  ///< Map of component arrays.
    ComponentType _nextComponentType = 0;  ///< The next component type identifier.
};

}  // namespace mobs

#endif  // COMPONENTMANAGER_H