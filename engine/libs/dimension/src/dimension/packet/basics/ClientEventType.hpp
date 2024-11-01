/**********************************************************************************
 *   Project: Dimension Network
 *   Description: Networking Game Library
 *   Author: Morgan LARGEOT, Maxence LARGEOT
 *   Create Time: 2024-10-23
 *   Location: Rennes
 **********************************************************************************/

#pragma once

#include <cstdint>

namespace dimension
{
enum ClientEventType : uint8_t
{
    ROOM = 1,
    MOVE = 2,
    ATTACK = 3,
    INTERRACTION = 4
};
}
