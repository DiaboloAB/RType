/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#pragma once

/**
 * @file Event.hpp
 * @brief Event enumeration for the Arcade project
 */

namespace RType
{

/**
 * @enum Event
 * @brief An enumeration to standardize events across libraries.
 *
 * This enumeration contains all possible event that can be used in the RType project.
 * It includes all the events that can be triggered by the user.
 */
enum KeyCode
{
    // Keyboard keys
    A, B, C, D, E, F, G, H, I, J, K, L, M,
    N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
    Comma, Dot, Tiret, Alpha0, Alpha1, Alpha2,
    Alpha3, Alpha4, Alpha5, Alpha6, Alpha7, Alpha8, Alpha9,
    UpArrow, DownArrow, LeftArrow, RightArrow,
    Escape, Space, Enter, Backspace, Tab, None,
    F1, F2, F3, F4, F5, F6, F7, F8, F9, F10,

    // Mouse buttons
    Mouse0, Mouse1, Mouse2, Mouse3, Mouse4, Mouse5, Mouse6,
    
    // Gamepad buttons
    ButtonA, ButtonB, ButtonX, ButtonY,       // Face buttons
    LeftBumper, RightBumper,                  // Shoulder buttons
    LeftTrigger, RightTrigger,                // Trigger buttons
    Start, Select,                            // Menu buttons
    LeftStickPress, RightStickPress,          // Pressable thumbsticks
    DPadUp, DPadDown, DPadLeft, DPadRight,    // D-Pad directions
    
    // Controller axes (for analog stick movement)
    LeftStickUp, LeftStickDown, LeftStickLeft, LeftStickRight,
    RightStickUp, RightStickDown, RightStickLeft, RightStickRight,

    // Additional controller keys
    Home, Share, Touchpad,                    // Special buttons on modern controllers
    Close                                      // Window close event
};
}  // namespace RType