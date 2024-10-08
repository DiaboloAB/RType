/*
** EPITECH PROJECT, 2024
** RType
** File description:
** PacketHandler.hpp
*/

#pragma once

#include <PacketManager/APacket.hpp>
#include <PacketManager/PacketValidationPacket.hpp>
#include <asio.hpp>
#include <list>
#include <memory>
#include <queue>

namespace RType::Network
{
class PacketHandler
{
   public:
    PacketHandler();
    ~PacketHandler();

   public:
    void insertToReceiveQueue(const std::shared_ptr<APacket> &packet,
                              const asio::ip::udp::endpoint &endpoint);
    void popReceiveQueue();
    void insertToValidationList(const APacket &packet, const asio::ip::udp::endpoint &endpoint);
    void deleteFromValidationList(const std::shared_ptr<PacketValidationPacket> &validation,
                                  const asio::ip::udp::endpoint &endpoint);
    bool needPacketValidation(const APacket &packet) const;

   public:
    std::queue<std::pair<std::shared_ptr<APacket>, asio::ip::udp::endpoint>> getReceiveQueue()
        const;
    std::list<std::pair<const APacket &, const asio::ip::udp::endpoint &>> getValidationList()
        const;

   private:
    std::queue<std::pair<std::shared_ptr<APacket>, asio::ip::udp::endpoint>> _receiveQueue;
    std::list<std::pair<const APacket &, const asio::ip::udp::endpoint &>> _validationList;
    std::list<PacketType> _needValidation = {HICLIENT, CREATEENTITY, DESTROYENTITY};
};
}  // namespace RType::Network
