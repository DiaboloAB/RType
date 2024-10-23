/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "GameContext.hpp"

// #include "RenderSystemSFML/RenderSystemSFML.hpp"
// std
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using namespace RType;

GameContext::GameContext(mobs::Registry &registry, SceneManager &sceneManager,
                         std::shared_ptr<IRuntime> runtime)
    : _runtime(runtime), _registry(registry), _sceneManager(sceneManager)
{
}

GameContext::~GameContext()
{
    // Destructor implementation
}
