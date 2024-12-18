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
    /**
     * @brief Handler of HiClient packet into the ECS from client side.
     *
     * @param registry: Reference to the entity-component registry.
     * @param gameContext: Reference to the game context.
     * @param packet: Update packet data & endpoint of packet sender.
     */
    static void handleHiClient(mobs::Registry &registry, GameContext &gameContext,
                               PacketDatas &packet)
    {

        gameContext.get<Text>("status").text = "status: connected";
        gameContext.get<Text>("status").color = mlg::vec3(0, 255, 0);
        LOG("ConnectionRedirect", "[HiClient packet] received");
    }

    /**
     * @brief Handler of Ping packet into the ECS from client side.
     *
     * @param registry: Reference to the entity-component registry.
     * @param gameContext: Reference to the game context.
     * @param packet: Update packet data & endpoint of packet sender.
     */
    static void handlePingClient(mobs::Registry &registry, GameContext &gameContext,
                                 PacketDatas &packet)
    {
        auto ping = std::dynamic_pointer_cast<dimension::Ping>(packet.first);
        auto &networkC = registry.get<NetworkClient>(registry.view<NetworkClient>().front());
        if (*networkC.client->getDirectionEndpoint() != packet.second && 
            *networkC.client->_serverEndpoint != packet.second)
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

    /**
     * @brief Handler of Ping packet into the ECS from room side.
     *
     * @param registry: Reference to the entity-component registry.
     * @param gameContext: Reference to the game context.
     * @param packet: Update packet data & endpoint of packet sender.
     */
    static void handlePingRoom(mobs::Registry &registry, GameContext &gameContext,
                               PacketDatas &packet)
    {
        auto ping = std::dynamic_pointer_cast<dimension::Ping>(packet.first);
        auto &networkC = registry.get<NetworkRoom>(registry.view<NetworkRoom>().front());
        if (!networkC.room->isConnected(packet.second)) return;
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
