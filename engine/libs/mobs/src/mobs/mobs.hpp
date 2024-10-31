/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef ANTIT_H
#define ANTIT_H

#include "component/ComponentManager.hpp"
#include "entity/EntityManager.hpp"

// std
#include <iostream>
#include <iterator>
#include <memory>
#include <unordered_map>

namespace mobs
{

/**
 * @brief The Registry class is the main
 * class of the library. It is used to create
 * entities and to manage their components.
 */
class Registry
{
   public:
    /**
     * @brief Construct a new Registry object
     */
    Registry();

    /**
     * @brief Destroy the Registry object
     */
    ~Registry();

    /**
     * @brief Create a new entity
     *
     * @return Entity The entity created
     */
    Entity create();

    /**
     * @brief Destroy an entity
     *
     * @param entity The entity to destroy
     */
    void kill(Entity entity);

    /**
     * @brief Adds a component to an entity.
     *
     * @tparam Component The type of the component to add.
     * @tparam Args The types of the arguments to pass to the component's constructor.
     * @param entity The entity to add the component to.
     * @param args The arguments to pass to the component's constructor.
     */
    template <typename Component, typename... Args>
    void emplace(Entity entity, Args &&...args)
    {
        Component component(std::forward<Args>(args)...);
        if (_componentManager.getComponentArray<Component>() == nullptr)
            _componentManager.registerComponent<Component>();
        Signature signature = _entityManager.getSignature(entity);
        signature.set(_componentManager.getComponentType<Component>(), true);
        _entityManager.setSignature(entity, signature);
        _componentManager.addComponent<Component>(entity, component);
    }

    /**
     * @brief Retrieves a component of a specific entity.
     *
     * @tparam Component The type of the component to retrieve.
     * @param entity The entity whose component is to be retrieved.
     * @return Reference to the component.
     */
    template <typename Component>
    Component &get(Entity entity)
    {
        return _componentManager.getComponent<Component>(entity);
    }

    /**
     * @struct View
     * @brief Provides an iterable view of entities and their components.
     */
    struct View
    {
        /**
         * @brief Returns an iterator to the beginning of the entities vector.
         *
         * @return Iterator to the beginning of the entities vector.
         */
        std::vector<Entity>::iterator begin() { return entities.begin(); }

        /**
         * @brief Returns an iterator to the end of the entities vector.
         *
         * @return Iterator to the end of the entities vector.
         */
        std::vector<Entity>::iterator end() { return entities.end(); }

        std::vector<Entity> entities;  ///< The entities in the view.
        ComponentManager _manager;     ///< The component manager.

        /**
         * @brief Retrieves a component of a specific entity within the view.
         *
         * @tparam Component The type of the component to retrieve.
         * @param entity The entity whose component is to be retrieved.
         * @return Reference to the component.
         */
        template <typename Component>
        Component &get(Entity entity)
        {
            return _manager.getComponent<Component>(entity);
        }

        /**
         * @brief Returns the number of entities in the view.
         *
         * @return The number of entities in the view.
         */
        Entity front() { return entities.front(); }
    };

    /**
     * @brief Creates a view of entities that have the specified components.
     *
     * @tparam Components The types of the components to filter entities by.
     * @return View The view of entities.
     */
    template <typename... Components>
    View view()
    {
        View view;
        std::vector<Entity> entities;
        for (Entity entity : _entityManager)
        {
            if (hasComponents<Components...>(entity)) entities.push_back(entity);
        }
        view.entities = entities;
        view._manager = _componentManager;
        return view;
    }

    /**
     * @brief Clears the registry.
     */
    void clear();

    template <typename Component>
    bool hasComponent(Entity entity)
    {
        Signature signature = _entityManager.getSignature(entity);
        ComponentType componentType = _componentManager.getComponentType<Component>();

        if (componentType == 255) return false;
        return signature.test(_componentManager.getComponentType<Component>());
    }

   private:
    EntityManager _entityManager;        ///< The entity manager.
    ComponentManager _componentManager;  ///< The component manager.

    /**
     * @brief Checks if an entity has the specified components.
     *
     * @tparam Components The types of the components to check.
     * @param entity The entity to check.
     * @return true If the entity has the specified components.
     * @return false If the entity does not have the specified components.
     */
    template <typename... Components>
    bool hasComponents(Entity entity)
    {
        Signature entitySignature = _entityManager.getSignature(entity);

        std::array<ComponentType, sizeof...(Components)> componentTypes = {
            _componentManager.getComponentType<Components>()...};
        for (ComponentType componentType : componentTypes)
        {
            if (componentType == 255) return false;
            if (!entitySignature.test(componentType)) return false;
        }
        return true;
    }
};

}  // namespace mobs

#endif  // MOBS_H