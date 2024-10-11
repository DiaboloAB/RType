/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "SystemManager.hpp"

using namespace RType;

SystemManager::SystemManager()
{
    // Constructor implementation
}

SystemManager::~SystemManager()
{
    // Destructor implementation
}

void SystemManager::start(mobs::Registry &registry, GameContext &gameContext)
{
    for (auto &system : _systems)
    {
        system->start(registry, gameContext);
    }
}

void SystemManager::update(mobs::Registry &registry, GameContext &gameContext)
{
    for (auto &system : _systems)
    {
        system->update(registry, gameContext);
    }
}

void SystemManager::draw(mobs::Registry &registry, GameContext &gameContext)
{
    for (auto &system : _systems)
    {
        system->draw(registry, gameContext);
    }
}
