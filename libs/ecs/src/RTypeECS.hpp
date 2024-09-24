/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef ANTIT_H
#define ANTIT_H


#include "entity/EntityManager.hpp"
#include "component/ComponentManager.hpp"

// std
#include <iostream>
#include <memory>
#include <unordered_map>

namespace RType::ECS
{

class Registry
{
   public:
    Registry();
    ~Registry();

    Entity create();
    void kill(Entity entity);

    template <typename Component, typename... Args>
    void emplace(Entity entity, Args&&... args)
    {
        Component component(std::forward<Args>(args)...);
        if (_componentManager.getComponentArray<Component>() == nullptr)
            _componentManager.registerComponent<Component>();
        _componentManager.addComponent<Component>(entity, component);
    }

    template <typename Component>
    Component &getComponent(Entity entity)
    {
        return _componentManager.getComponent<Component>(entity);
    }

    // Getters

    // Setters

   private:
    EntityManager _entityManager;
    ComponentManager _componentManager;
    // Member variables
};

}  // namespace RType::ECS

#endif  // ANTIT_H