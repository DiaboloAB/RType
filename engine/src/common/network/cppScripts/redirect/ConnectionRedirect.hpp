/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef CONNECTIONREDIRECT_HPP
#define CONNECTIONREDIRECT_HPP

#include "common/ICppScript.hpp"
#include "gameContext/GameContext.hpp"

namespace RType::Network
{
class ConnectionRedirect
{
   private:
    using PacketDatas = std::pair<std::shared_ptr<dimension::APacket>, asio::ip::udp::endpoint>;

   public:
    static void handleHiClient(mobs::Registry &registry, GameContext &gameContext,
                               PacketDatas &packet)
    {
        LOG("ConnectionRedirect", "[HiClient packet] received");
    }

    static void handlePingClient(mobs::Registry &registry, GameContext &gameContext,
                                 PacketDatas &packet)
    {
        auto ping = std::dynamic_pointer_cast<dimension::Ping>(packet.first);
        auto &networkC = registry.get<NetworkClient>(registry.view<NetworkClient>().front());
        if (*networkC.client->getDirectionEndpoint() != packet.second)
        {
            ERR_LOG("handleConnection", "Invalid sender of packets.");
            return;
        }
        if (ping->getRecepTs() == 0) {
            ping->setRecepTs(std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now().time_since_epoch()).count());
            return networkC.client->send(ping, packet.second, false);
        }
        uint64_t currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(
                                std::chrono::system_clock::now().time_since_epoch()).count();
        networkC.latency = currentTime - ping->getPacketTimeStamp();
        LOG("ConnectionRedirect",
            "[Ping packet] received, latence:" + std::to_string(networkC.latency) + "ms.");
    }

    static void handlePingRoom(mobs::Registry &registry, GameContext &gameContext,
                               PacketDatas &packet)
    {
        auto ping = std::dynamic_pointer_cast<dimension::Ping>(packet.first);
        auto &networkC = registry.get<NetworkRoom>(registry.view<NetworkRoom>().front());
        if (ping->getRecepTs() != 0) networkC.room->setSenderLatency(packet.second, ping->getPacketTimeStamp());
        networkC.room->resetPing(packet.second);
        ping->setRecepTs(std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()).count());
        networkC.room->send(ping, packet.second, false);
        LOG("ConnectionRedirect",
            "[Ping packet] received, latence:" + std::to_string(0) + "ms.");
    }
};
}  // namespace RType::Network

#endif  // CONNECTIONREDIRECT_HPP
