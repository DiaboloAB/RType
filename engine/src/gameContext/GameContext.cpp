/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "GameContext.hpp"

// std
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using namespace RType;

GameContext::GameContext(std::string assetsPath, mobs::Registry &registry,
                         SceneManager &sceneManager, ClockManager &clockManager, std::shared_ptr<IRuntime> runtime)
    : _assetsPath(assetsPath), _runtime(runtime), _registry(registry), _sceneManager(sceneManager), _clockManager(clockManager)
{
}

GameContext::~GameContext()
{
    // Destructor implementation
}
