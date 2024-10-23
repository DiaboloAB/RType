/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#pragma once

#include "packet/PacketFactory.hpp"

#include "networkPacket/packets/AdiosServerPacket.hpp"
#include "networkPacket/packets/ClientEventPacket.hpp"
#include "networkPacket/packets/CreateEntityPacket.hpp"
#include "networkPacket/packets/DestroyEntityPacket.hpp"
#include "networkPacket/packets/HiClientPacket.hpp"
#include "networkPacket/packets/HiServerPacket.hpp"
#include "networkPacket/packets/MoveEntityPacket.hpp"
#include "networkPacket/packets/PacketValidationPacket.hpp"
#include "networkPacket/packets/PingPacket.hpp"
#include "networkPacket/packets/UpdateEntityPacket.hpp"

namespace RType::Network
{

/**
 * @class PacketFactory
 *
 * @brief This class is a design pattern use to create all types of packets. These packets
 * are used for network communication between client and server.
 */
class PacketFactory : public dimension::PacketFactory
{
   public:
    PacketFactory();
    ~PacketFactory();
};
}  // namespace RType::Network
