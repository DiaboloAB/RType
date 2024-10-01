/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "GameContext.hpp"
#include <nlohmann/json.hpp>

#include <iostream>
#include <fstream>

using namespace RType;

GameContext::GameContext() {
    std::ifstream i("assets/game.json");

    if (!i.is_open()) {
        std::cerr << "Error: Could not open file" << std::endl;
        throw std::runtime_error("Could not open file");
    }
    nlohmann::json j;
    i >> j;

    std::cout << j.dump(4) << std::endl;
    // name = j["name"];

    _runtime = new RenderSystemSFML();
    _currentTime = std::chrono::high_resolution_clock::now();
    _deltaT = 0.0f;
    // Constructor implementation
}

GameContext::~GameContext() {
    // Destructor implementation
}