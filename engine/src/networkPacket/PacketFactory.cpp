/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "PacketFactory.hpp"

namespace RType::Network
{
PacketFactory::PacketFactory()
{
    this->initRegisterSendCreator();
    this->initRegisterDeserializationCreator();
}

PacketFactory::~PacketFactory() {}

void PacketFactory::initRegisterSendCreator() {
    this->_packetManager.registerPacketToSend<HiServerPacket>();
    this->_packetManager.registerPacketToSend<HiClientPacket>();
    this->_packetManager.registerPacketToSend<AdiosServerPacket>();
    this->_packetManager.registerPacketToSend<PingPacket>();
    this->_packetManager.registerPacketToSend<CreateEntityPacket>();
    this->_packetManager.registerPacketToSend<DestroyEntityPacket>();
    this->_packetManager.registerPacketToSend<MoveEntityPacket>();
    this->_packetManager.registerPacketToSend<UpdateEntityPacket>();
    this->_packetManager.registerPacketToSend<ClientEventPacket>();
    this->_packetManager.registerPacketToSend<PacketValidationPacket>();
}

void PacketFactory::initRegisterDeserializationCreator() {
    this->_packetManager.registerPacketDeserialization<HiServerPacket>(HISERVER);
    this->_packetManager.registerPacketDeserialization<HiClientPacket>(HICLIENT);
    this->_packetManager.registerPacketDeserialization<AdiosServerPacket>(ADIOSSERVER);
    this->_packetManager.registerPacketDeserialization<PingPacket>(PING);
    this->_packetManager.registerPacketDeserialization<CreateEntityPacket>(CREATEENTITY);
    this->_packetManager.registerPacketDeserialization<DestroyEntityPacket>(DESTROYENTITY);
    this->_packetManager.registerPacketDeserialization<MoveEntityPacket>(MOVEENTITY);
    this->_packetManager.registerPacketDeserialization<UpdateEntityPacket>(UPDATEENTITY);
    this->_packetManager.registerPacketDeserialization<ClientEventPacket>(CLIENTEVENT);
    this->_packetManager.registerPacketDeserialization<PacketValidationPacket>(PACKETVALIDATION);
}
}  // namespace RType::Network
