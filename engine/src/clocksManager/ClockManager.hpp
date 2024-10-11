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

/**
 * @class ClockManager
 * @brief Manages the timing and delta times for the game engine.
 */
class ClockManager {
public:
    /**
     * @brief Constructs a new ClockManager object.
     */
    ClockManager();

    /**
     * @brief Destroys the ClockManager object.
     */
    ~ClockManager();

    /**
     * @brief Updates the clock manager, calculating delta times.
     */
    void update();

    /**
     * @brief Gets the delta time.
     * @return The delta time.
     */
    float getDeltaT() const { return _deltaT; }

    /**
     * @brief Gets the update delta time.
     * @return Reference to the update delta time.
     */
    float &getUpdateDeltaT() { return _updateDeltaT; }

    /**
     * @brief Gets the draw delta time.
     * @return Reference to the draw delta time.
     */
    float &getDrawDeltaT() { return _drawDeltaT; }

    /**
     * @brief Gets the target update delta time.
     * @return The target update delta time.
     */
    float getTargetUpdateDeltaT() const { return _targetUpdateDeltaT; }

    /**
     * @brief Gets the target draw delta time.
     * @return The target draw delta time.
     */
    float getTargetDrawDeltaT() const { return _targetDrawDeltaT; }

    /**
     * @brief Sets the target update delta time.
     * @param targetUpdateDeltaT The target update delta time.
     */
    void setTargetUpdateDeltaT(float targetUpdateDeltaT) { _targetUpdateDeltaT = targetUpdateDeltaT; }

    /**
     * @brief Sets the target draw delta time.
     * @param targetDrawDeltaT The target draw delta time.
     */
    void setTargetDrawDeltaT(float targetDrawDeltaT) { _targetDrawDeltaT = targetDrawDeltaT; }

private:
    std::chrono::high_resolution_clock::time_point _currentTime =
        std::chrono::high_resolution_clock::now(); ///< The current time.
    float _deltaT = 0.0f; ///< The delta time.
    float _updateDeltaT = 0.0f; ///< The update delta time.
    float _drawDeltaT = 0.0f; ///< The draw delta time.
    float _targetUpdateDeltaT = 1.0f / 300.0f; ///< The target update delta time.
    float _targetDrawDeltaT = 1.0f / 60.0f; ///< The target draw delta time.
};

#endif // CLOCKMANAGER_H