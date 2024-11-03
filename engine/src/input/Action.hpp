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
    Action(const std::vector<KeyCode> keys, bool keyDown = true) : _keys(keys), _keyDown(keyDown) {
        for (auto key : _keys) {
            std::cout << "Key: " << key << std::endl;
        }
    };
    ~Action() {};

    void update(std::shared_ptr<IRuntime> runtime) {
        bool value = false;
        for (auto key : _keys) {
            if (_keyDown ? runtime->getKeyDown(key) : runtime->getKey(key)) {
                value = true;
            }
        }
        _value = value;
    }

    bool get() const { return _value; }

private:
    std::vector<KeyCode> _keys;
    bool _keyDown = false;

    bool _value = false;
};

} // namespace RType

#endif // ACTION_H