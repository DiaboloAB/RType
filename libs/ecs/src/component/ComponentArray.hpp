/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef COMPONENTARRAY_H
#define COMPONENTARRAY_H

// #include "Entity.hpp"

// std
#include <vector>

namespace RType::ECS {

class ComponentArray {
public:
    ComponentArray();
    ~ComponentArray();

    // void insertComponent(Entity entity, Component component)
    // {
    //     if (entity >= _components.size())
    //         _components.resize(entity + 1);
    //     _components[entity] = component;
    // }

    // void removeComponent(Entity entity)
    // {
    //     cassert(entity >= _components.size(), "Entity out of range");
    //     _components[entity].reset();
    // }

    // Getters

    // Setters

private:
    // Member variables
    std::vector<std::optional<Component>> _components;
};

} // namespace RType::ECS

#endif // COMPONENTARRAY_H