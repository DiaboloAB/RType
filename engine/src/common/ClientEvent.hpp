/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#pragma once

#include <cstdint>

namespace RType::Network
{
enum ClientEvent : uint8_t
{
    GAME_START = 0,
    MOVE_UP = 1,
    STOP_MOVE_UP = 2,
    MOVE_DOWN = 3,
    STOP_MOVE_DOWN = 4,
    MOVE_LEFT = 5,
    STOP_MOVE_LEFT = 6,
    MOVE_RIGHT = 7,
    STOP_MOVE_RIGHT = 8,
    SHOOT = 9,
    HOLD_SHOOT = 10,
};
}
