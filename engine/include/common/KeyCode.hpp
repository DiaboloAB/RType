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
        Close,  // Close the window
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,
        Comma,
        Dot,
        Tiret,
        Alpha0,
        Alpha1,
        Alpha2,
        Alpha3,
        Alpha4,
        Alpha5,
        Alpha6,
        Alpha7,
        Alpha8,
        Alpha9,
        Mouse0,
        Mouse2,
        Mouse3,
        Mouse4,
        Mouse5,
        Mouse6,
        UpArrow,
        DownArrow,
        LeftArrow,
        RightArrow,
        Escape,
        Space,
        Enter,
        Backspace,
        Tab,
        None
    };
    }  // namespace RType