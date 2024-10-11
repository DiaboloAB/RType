/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "ClockManager.hpp"

ClockManager::ClockManager() {
    // Constructor implementation
}

ClockManager::~ClockManager() {
    // Destructor implementation
}

void ClockManager::update() {
    std::chrono::high_resolution_clock::time_point newTime =
        std::chrono::high_resolution_clock::now();
    float elapsed =
        std::chrono::duration<float, std::chrono::seconds::period>(newTime - _currentTime)
            .count();
    _deltaT = elapsed;
    _drawDeltaT += elapsed;
    _updateDeltaT += elapsed;
    _currentTime = newTime;
}