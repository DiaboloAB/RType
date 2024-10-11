/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef CLOCKMANAGER_H
#define CLOCKMANAGER_H

// std
#include <chrono>

class ClockManager {
public:
    ClockManager();
    ~ClockManager();

    void update();

    float getDeltaT() const { return _deltaT; }
    float &getUpdateDeltaT() { return _updateDeltaT; }
    float &getDrawDeltaT() { return _drawDeltaT; }
    float getTargetUpdateDeltaT() const { return _targetUpdateDeltaT; }
    float getTargetDrawDeltaT() const { return _targetDrawDeltaT; }

    void setTargetUpdateDeltaT(float targetUpdateDeltaT) { _targetUpdateDeltaT = targetUpdateDeltaT; }
    void setTargetDrawDeltaT(float targetDrawDeltaT) { _targetDrawDeltaT = targetDrawDeltaT; }

private:
    std::chrono::high_resolution_clock::time_point _currentTime =
        std::chrono::high_resolution_clock::now(); ///< The current time.
    float _deltaT = 0.0f; ///< The delta time.
    float _updateDeltaT = 0.0f; ///< The update delta time.
    float _drawDeltaT = 0.0f; ///< The draw delta time.
    float _targetUpdateDeltaT = 1.0f / 300.0f; ///< The target update delta time.
    float _targetDrawDeltaT = 1.0f / 60.0f; ///< The target draw delta time.
    // Member variables
};

#endif // CLOCKMANAGER_H