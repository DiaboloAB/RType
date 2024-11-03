/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef AXIS_H
#define AXIS_H

#include "common/KeyCode.hpp"
#include <vector>
#include "IRuntime/IRuntime.hpp"

namespace RType {

class Axis {
public:
    Axis() {};
    Axis(const std::vector<KeyCode> positiveKeys, const std::vector<KeyCode> negativeKeys, bool keyDown = true) : _positiveKeys(positiveKeys), _negativeKeys(negativeKeys), _keyDown(keyDown) {};
    ~Axis() {};

    void update(std::shared_ptr<IRuntime> runtime) {
        int value = 0;
        for (auto key : _positiveKeys) {
            if (_keyDown ? runtime->getKeyDown(key) : runtime->getKey(key)) {
                value++;
            }
        }
        for (auto key : _negativeKeys) {
            if (_keyDown ? runtime->getKeyDown(key) : runtime->getKey(key)) {
                value--;
            }
        }
        _value = value;
    }

    int get() const { return _value; }

private:
    std::vector<KeyCode> _positiveKeys;
    std::vector<KeyCode> _negativeKeys;
    bool _keyDown = false;

    int _value = 0;
};

} // namespace RType

#endif // AXIS_H