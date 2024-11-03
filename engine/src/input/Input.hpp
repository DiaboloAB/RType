/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef INPUT_H
#define INPUT_H

#include "Action.hpp"
#include "Axis.hpp"
#include "IRuntime/IRuntime.hpp"
// std
#include <map>
#include <string>

namespace RType {

class Input {
public:
    Input() {
        addAction("Up", Action({ KeyCode::UpArrow, KeyCode::LeftStickUp }));
        addAction("Down", Action({ KeyCode::DownArrow, KeyCode::LeftStickDown }));
        addAction("Left", Action({ KeyCode::LeftArrow, KeyCode::LeftStickLeft }));
        addAction("Right", Action({ KeyCode::RightArrow, KeyCode::LeftStickRight }));
        addAction("Action1", Action({ KeyCode::Enter, KeyCode::ButtonA }));
        addAction("Action2", Action({ KeyCode::Escape, KeyCode::ButtonB }));
        // Default axes
        // addAxis("Horizontal", Axis({ KeyCode::Right }, { KeyCode::Left }));
        // addAxis("Vertical", Axis({ KeyCode::Down }, { KeyCode::Up }));
    };
    ~Input() {};

    void update(std::shared_ptr<IRuntime> runtime) {
        for (auto& action : _actions) {
            action.second.update(runtime);
        }
        for (auto& axis : _axes) {
            axis.second.update(runtime);
        }
    }

    bool getAction(const std::string& name) const {
        auto it = _actions.find(name);
        if (it == _actions.end()) {
            return false;
        }
        return it->second.get();
    }

    int getAxis(const std::string& name) const {
        auto it = _axes.find(name);
        if (it == _axes.end()) {
            return 0;
        }
        return it->second.get();
    }

private:
    std::map<std::string, Action> _actions;
    std::map<std::string, Axis> _axes;

    void addAction(const std::string& name, const Action& action) {
        _actions[name] = action;
    }

    void addAxis(const std::string& name, const Axis& axis) {
        _axes[name] = axis;
    }
};

} // namespace RType

#endif // INPUT_H