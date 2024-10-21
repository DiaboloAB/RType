/**********************************************************************************
 *  Project: Dimension Network
 *  Description: Networking Game Library
 *  Author: Morgan LARGEOT, Maxence LARGEOT
 *  Create Time: 2024-10-18
 *  Location: Rennes
  **********************************************************************************/

#include "APacketFactory.hpp"

namespace dimension {
APacketFactory::APacketFactory() {
    this->_packetManager.registerPacket<HiServer>();
    this->_packetManager.registerPacket<HiClient>();
    this->_packetManager.registerPacket<AdiosServer>();
    this->_packetManager.registerPacket<Ping>();
    this->_packetManager.registerPacket<CreateEntity>();
    this->_packetManager.registerPacket<DestroyEntity>();
    this->_packetManager.registerPacket<MoveEntity>();
    this->_packetManager.registerPacket<UpdateEntity>();
    this->_packetManager.registerPacket<ClientEvent>();
    this->_packetManager.registerPacket<PacketValidation>();
};
}