/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef INPUT_H
#define INPUT_H

// std
#include <unordered_map>

namespace RType {

enum KeyCode {
    Space = 32,
    Left = 263,
    Right = 262,
    Up = 265,
    Down = 264,
    Escape = 256,
    Enter = 257,
    A = 65,
    D = 68,
    S = 83,
    W = 87,
    Q = 81,
    E = 69,
    R = 82,
    F = 70,
    G = 71,
    H = 72,
    J = 74,
    K = 75,
    L = 76,
    Z = 90,
    X = 88,
    C = 67,
    V = 86,
    B = 66,
    N = 78,
    M = 77,
    Comma = 44,
    Period = 46,
    Slash = 47,
    Zero = 48,
}

class Input {
public:
    Input();
    ~Input();

    void update(const std::vector<int>& keys) {
        _previousKeys = _currentKeys;
        _currentKeys.clear();
        for (int key : keys) {
            _currentKeys[key] = true;
        }
    }

    bool getKey(KeyCode key) {
        return _currentKeys[key];
    }

    bool getKeyDown(KeyCode key) {
        return _currentKeys[key] && !_previousKeys[key];
    }

    bool getKeyUp(KeyCode key) {
        return !_currentKeys[key] && _previousKeys[key];
    }

private:
    std::unordered_map<int, bool> _currentKeys;
    std::unordered_map<int, bool> _previousKeys;
    // Member variables
};
}

#endif // INPUT_H