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
    this->_packetManager.registerPacket<HiServerPacket>();
    this->_packetManager.registerPacket<HiClientPacket>();
    this->_packetManager.registerPacket<AdiosServerPacket>();
    this->_packetManager.registerPacket<PingPacket>();
    this->_packetManager.registerPacket<CreateEntityPacket>();
    this->_packetManager.registerPacket<DestroyEntityPacket>();
    this->_packetManager.registerPacket<MoveEntityPacket>();
    this->_packetManager.registerPacket<UpdateEntityPacket>();
    this->_packetManager.registerPacket<ClientEventPacket>();
    this->_packetManager.registerPacket<PacketValidationPacket>();
}

PacketFactory::~PacketFactory() {}

}  // namespace RType::Network
