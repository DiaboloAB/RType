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

class Registry
{
   public:
    Registry();
    ~Registry();

    Entity create();
    void kill(Entity entity);

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

    template <typename Component>
    Component &get(Entity entity)
    {
        return _componentManager.getComponent<Component>(entity);
    }

    struct View
    {
        std::vector<Entity>::iterator begin() { return entities.begin(); }
        std::vector<Entity>::iterator end() { return entities.end(); }

        std::vector<Entity> entities;
        ComponentManager _manager;

        template <typename Component>
        Component &get(Entity entity)
        {
            return _manager.getComponent<Component>(entity);
        }
    };

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
        // return entities;
    }

    void clear()
    {
        for (Entity entity : _entityManager)
        {
            kill(entity);
        }
    }

    EntityManager _entityManager;

   private:
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

    ComponentManager _componentManager;
    // Member variables
};

}  // namespace mobs

#endif  // MOBS_H