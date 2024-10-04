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

using Entity = std::uint32_t;
const Entity MAX_ENTITIES = 5000;

using ComponentType = std::uint8_t;
const ComponentType MAX_COMPONENTS = 32;
using Signature = std::bitset<MAX_COMPONENTS>;

class EntityManager
{
   public:
    EntityManager();
    ~EntityManager();

    Entity create();
    void kill(Entity entity);

    // Getters
    Signature getSignature(Entity entity);
    int getNbLivingEntity() { return _nbLivingEntity; }

    // Setters
    void setSignature(Entity entity, Signature signature);

    // Iterators
    std::vector<Entity>::iterator begin() { return _entities.begin(); }
    std::vector<Entity>::iterator end() { return _entities.end(); }

   private:
    // Member variables
    std::queue<Entity> _availableEntities{};
    std::array<Signature, MAX_ENTITIES> _signatures{};
    size_t _nbLivingEntity{};

    std::vector<Entity> _entities{};
};

}  // namespace mobs

#endif  // ENTITYMANAGER_H