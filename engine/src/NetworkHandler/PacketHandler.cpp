/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "PacketHandler.hpp"

namespace RType::Network
{

PacketHandler::PacketHandler(){};

PacketHandler::~PacketHandler(){};

void PacketHandler::insertToReceiveQueue(const std::shared_ptr<APacket> &packet,
                                         const asio::ip::udp::endpoint &enpoint)
{
    this->_receiveQueue.push(
        std::pair<std::shared_ptr<APacket>, asio::ip::udp::endpoint>(packet, enpoint));
}

void PacketHandler::popReceiveQueue()
{
    if (!this->_receiveQueue.empty()) this->_receiveQueue.pop();
}

void PacketHandler::insertToValidationList(const APacket &packet,
                                           const asio::ip::udp::endpoint &endpoint)
{
    this->_validationList.emplace_back(
        std::pair<const APacket &, const asio::ip::udp::endpoint &>(packet, endpoint));
}

void PacketHandler::deleteFromValidationList(
    const std::shared_ptr<PacketValidationPacket> &validation,
    const asio::ip::udp::endpoint &endpoint)
{
    for (auto packetInValidation = this->_validationList.begin();
         packetInValidation != this->_validationList.end();)
    {
        PacketType packetType = packetInValidation->first.getPacketType();
        uint64_t packetTimeStamp = packetInValidation->first.getPacketTimeStamp();
        if (validation->getPacketReceiveType() == packetType &&
            validation->getPacketReceiveTimeStamp() && endpoint == packetInValidation->second)
        {
            this->_validationList.erase(packetInValidation);
            break;
        }
        else
            packetInValidation++;
    }
}

bool PacketHandler::needPacketValidation(const APacket &packet) const
{
    PacketType type = packet.getPacketType();
    for (auto &typeValidation : this->_needValidation)
    {
        if (typeValidation == type) return true;
    }
    return false;
}

std::queue<std::pair<std::shared_ptr<APacket>, asio::ip::udp::endpoint>>
PacketHandler::getReceiveQueue() const
{
    return this->_receiveQueue;
}

std::list<std::pair<const APacket &, const asio::ip::udp::endpoint &>>
PacketHandler::getValidationList() const
{
    return this->_validationList;
}
}  // namespace RType::Network