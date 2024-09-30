/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "GameContext.hpp"

using namespace RType;

GameContext::GameContext() {
    _runtime = new RenderSystemSFML();
    _currentTime = std::chrono::high_resolution_clock::now();
    _deltaT = 0.0f; 
    // Constructor implementation
}

GameContext::~GameContext() {
    // Destructor implementation
}