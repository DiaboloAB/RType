/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "PacketFactory.hpp"

namespace RType::Network {
PacketFactory::PacketFactory() {
    this->_creationMap[HISERVER] = [](std::vector<char> &buffer) {return std::make_shared<HiServerPacket>(buffer);};
    this->_creationMap[HICLIENT] = [](std::vector<char> &buffer) {return std::make_shared<HiClientPacket>(buffer);};
    this->_creationMap[ADIOSSERVER] = [](std::vector<char> &buffer) {return std::make_shared<AdiosServerPacket>(buffer);};
    this->_creationMap[HEALTHCHECK] = [](std::vector<char> &buffer) {return std::make_shared<HealthcheckPacket>(buffer);};
    this->_creationMap[CREATEENTITY] = [](std::vector<char> &buffer) {return std::make_shared<CreateEntityPacket>(buffer);};
    this->_creationMap[DESTROYENTITY] = [](std::vector<char> &buffer) {return std::make_shared<DestroyEntityPacket>(buffer);};
    this->_creationMap[MOVEENTITY] = [](std::vector<char> &buffer) {return std::make_shared<MoveEntityPacket>(buffer);};
    this->_creationMap[UPDATEENTITY] = [](std::vector<char> &buffer) {return std::make_shared<UpdateEntityPacket>(buffer);};
    this->_creationMap[CLIENTEVENT] = [](std::vector<char> &buffer) {return std::make_shared<ClientEventPacket>(buffer);};
    this->_creationMap[KICKCLIENT] = [](std::vector<char> &buffer) {return std::make_shared<KickClientPacket>(buffer);};
    this->_creationMap[PACKETVALIDATION] = [](std::vector<char> &buffer) {return std::make_shared<KickClientPacket>(buffer);};
}

PacketFactory::PacketFactory(const PacketFactory &obj) {
    this->_creationMap = obj._creationMap;
}

PacketFactory::~PacketFactory() {}

std::unordered_map<PacketType, std::function<std::shared_ptr<APacket>(std::vector<char> &)>> PacketFactory::getCreationMap() const {
    return this->_creationMap;
}

std::shared_ptr<APacket> PacketFactory::createPacketFromBuffer(std::vector<char> &buffer) {
    try {
        uint32_t packetSize = APacket::getPacketSizeFromBuffer(buffer);
        PacketType type = APacket::getPacketTypeFromBuffer(buffer);

        if (packetSize > buffer.size())
            throw PacketFactoryError("PacketFactoryError: Something wrong with packet size, probably incomplete.");
        return this->_creationMap[type](buffer);
    } catch (std::exception &e) {
        throw;
    }
}
}
