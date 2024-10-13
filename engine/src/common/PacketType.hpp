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
/**
 * @enum PacketType
 * @brief Defines all possible types of packets that can be sent or received.
 */
enum PacketType : uint8_t
{
    NONE = 0,
    HISERVER = 1,
    HICLIENT = 2,
    ADIOSSERVER = 3,
    PING = 4,
    CREATEENTITY = 5,
    DESTROYENTITY = 6,
    MOVEENTITY = 7,
    UPDATEENTITY = 8,
    CLIENTEVENT = 9,
    PACKETVALIDATION = 10,
};
}  // namespace RType::Network