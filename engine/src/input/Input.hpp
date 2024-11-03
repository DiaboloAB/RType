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
    };
    ~Input() {};

    /**
     * @brief Updates the input.
     * @param runtime The runtime system.
     * 
     * This method updates the input by checking if any of the keys are pressed.
     */
    void update(std::shared_ptr<IRuntime> runtime) {
        for (auto& action : _actions) {
            action.second.update(runtime);
        }
        for (auto& axis : _axes) {
            axis.second.update(runtime);
        }
    }

    /**
     * @brief Gets the value of the action.
     * @param name The name of the action.
     * @return The value of the action.
     */
    bool getAction(const std::string& name) const {
        auto it = _actions.find(name);
        if (it == _actions.end()) {
            return false;
        }
        return it->second.get();
    }

    /**
     * @brief Gets the value of the axis.
     * @param name The name of the axis.
     * @return The value of the axis.
     */
    int getAxis(const std::string& name) const {
        auto it = _axes.find(name);
        if (it == _axes.end()) {
            return 0;
        }
        return it->second.get();
    }

private:
    std::map<std::string, Action> _actions; ///< The actions.
    std::map<std::string, Axis> _axes; ///< The axes.

    /**
     * @brief Adds an action.
     * @param name The name of the action.
     * @param action The action.
     */
    void addAction(const std::string& name, const Action& action) {
        _actions[name] = action;
    }

    /**
     * @brief Adds an axis.
     * @param name The name of the axis.
     * @param axis The axis.
     */
    void addAxis(const std::string& name, const Axis& axis) {
        _axes[name] = axis;
    }
};

} // namespace RType

#endif // INPUT_H