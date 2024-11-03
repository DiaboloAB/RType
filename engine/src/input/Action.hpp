/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef ACTION_H
#define ACTION_H

#include "common/KeyCode.hpp"
#include <vector>
#include "IRuntime/IRuntime.hpp"

// std

namespace RType {

class Action {
public:
    Action() {};
    Action(const std::vector<KeyCode> keys, bool keyDown = true) : _keys(keys), _keyDown(keyDown) {};
    ~Action() {};

    /**
     * @brief Updates the action.
     * @param runtime The runtime system.
     * 
     * This method updates the action by checking if any of the keys are pressed.
     */
    void update(std::shared_ptr<IRuntime> runtime) {
        bool value = false;
        for (auto key : _keys) {
            if (_keyDown ? runtime->getKeyDown(key) : runtime->getKey(key)) {
                value = true;
            }
        }
        _value = value;
    }

    /**
     * @brief Gets the value of the action.
     * @return The value of the action.
     */
    bool get() const { return _value; }

private:
    std::vector<KeyCode> _keys; ///< The keys associated with the action.
    bool _keyDown = false; ///< Whether the keys should be checked for key down or key up.

    bool _value = false; ///< The value of the action.
};

} // namespace RType

#endif // ACTION_H