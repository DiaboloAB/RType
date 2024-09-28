/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef GAMECONTEXT_H
#define GAMECONTEXT_H

// std
#include <chrono>

namespace RType
{

class GameContext {
public:
    GameContext();
    ~GameContext();

    void update() {
        std::chrono::high_resolution_clock::time_point newTime = std::chrono::high_resolution_clock::now();
        _deltaT = std::chrono::duration<float, std::chrono::seconds::period>(newTime - _currentTime).count();
        _currentTime = newTime;
    }

    float _deltaT;

private:
    // Member variables
    std::chrono::high_resolution_clock::time_point _currentTime;
    //renderer here
};

}  // namespace RType

#endif // GAMECONTEXT_H