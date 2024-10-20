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
    //this->_packetManager.registerPacket<PingPacket>();
    //this->_packetManager.registerPacket<CreateEntityPacket>();
    //this->_packetManager.registerPacket<DestroyEntityPacket>();
    //this->_packetManager.registerPacket<MoveEntityPacket>();
    //this->_packetManager.registerPacket<UpdateEntityPacket>();
    //this->_packetManager.registerPacket<ClientEventPacket>();
    //this->_packetManager.registerPacket<PacketValidationPacket>();
};
}