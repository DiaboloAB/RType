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
    std::cout << "SystemManager: Starting systems" << std::endl;
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

void SystemManager::load(mobs::Registry &registry, GameContext &gameContext)
{
    for (auto &system : _systems)
    {
        system->load(registry, gameContext);
    }
}

void SystemManager::stop(mobs::Registry &registry, GameContext &gameContext)
{
    for (auto &system : _systems)
    {
        system->stop(registry, gameContext);
    }
}
