/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "EntityManager.hpp"

using namespace RType::ECS;

EntityManager::EntityManager()
{
    for (Entity entity = 0; entity < MAX_ENTITIES; entity++)
    {
        _availableEntities.push(entity);
    }
}

EntityManager::~EntityManager() {}

Entity EntityManager::create()
{
    assert(_nbLivingEntity < MAX_ENTITIES && "Too many entities in existence.");

    Entity id = _availableEntities.front();
    _availableEntities.pop();
    _nbLivingEntity++;
    _entities.push_back(id);
    return id;
}

void EntityManager::kill(Entity entity)
{
    assert(entity < MAX_ENTITIES && "Entity out of range.");

    _signatures[entity].reset();
    _availableEntities.push(entity);
    int index = 0;
    for (auto &e : _entities)
    {
        if (e == entity)
            break;
        index++;
    }
    _entities.erase(_entities.begin() + index);
    _nbLivingEntity--;
}

void EntityManager::setSignature(Entity entity, Signature signature)
{
    assert(entity < MAX_ENTITIES && "Entity out of range.");

    _signatures[entity] = signature;
}

Signature EntityManager::getSignature(Entity entity)
{
    assert(entity < MAX_ENTITIES && "Entity out of range.");

    return _signatures[entity];
}
