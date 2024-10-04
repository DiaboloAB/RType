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

class ComponentManager
{
   public:
    ComponentManager();
    ~ComponentManager();

    template <typename Component>
    void registerComponent()
    {
        const std::type_index typeIndex(typeid(Component));
        _componentTypes[typeIndex] = _nextComponentType++;
        _componentArrays[typeIndex] = std::make_shared<ComponentArray<Component>>();
    }

    template <typename Component>
    ComponentType getComponentType()
    {
        const std::type_index typeIndex(typeid(Component));
        return _componentTypes[typeIndex];
    }

    template <typename Component>
    std::shared_ptr<ComponentArray<Component>> getComponentArray()
    {
        const std::type_index typeIndex(typeid(Component));
        return std::static_pointer_cast<ComponentArray<Component>>(_componentArrays[typeIndex]);
    }

    template <typename Component>
    void addComponent(Entity entity, Component component)
    {
        getComponentArray<Component>()->insertComponent(entity, component);
    }

    template <typename Component>
    void removeComponent(Entity entity)
    {
        getComponentArray<Component>()->removeComponent(entity);
    }

    template <typename Component>
    Component& getComponent(Entity entity)
    {
        return getComponentArray<Component>()->getComponent(entity);
    }

    void entityDestroyed(Entity entity)
    {
        for (auto const& pair : _componentArrays)
        {
            auto const& component = pair.second;
            component->entityDestroyed(entity);
        }
    }

   private:
    std::unordered_map<std::type_index, ComponentType> _componentTypes;
    std::unordered_map<std::type_index, std::shared_ptr<IComponentArray>> _componentArrays;
    ComponentType _nextComponentType = 0;
};

}  // namespace mobs

#endif  // COMPONENTMANAGER_H