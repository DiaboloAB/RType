/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef COMPONENTARRAY_H
#define COMPONENTARRAY_H

#include "entity/EntityManager.hpp"

// std
#include <memory>
#include <optional>
#include <vector>

namespace RType::ECS
{

class IComponentArray
{
   public:
    virtual ~IComponentArray() = default;
    virtual void entityDestroyed(Entity entity) = 0;
};

template <typename Component>
class ComponentArray : public IComponentArray
{
   public:
    ComponentArray() = default;
    ~ComponentArray() = default;

    void insertComponent(Entity entity, Component component)
    {
        if (entity >= _components.size()) _components.resize(entity + 1);
        _components[entity] = component;
    }

    void removeComponent(Entity entity) { _components[entity].reset(); }

    Component& getComponent(Entity entity) { return _components[entity].value(); }

    void entityDestroyed(Entity entity) override
    {
        if (entity >= _components.size()) return;
        if (_components[entity].has_value()) _components[entity].reset();
        _components[entity].reset();
    }

    // Getters

    // Setters

   private:
    // Member variables
    std::vector<std::optional<Component>> _components;
};

}  // namespace RType::ECS

#endif  // COMPONENTARRAY_H