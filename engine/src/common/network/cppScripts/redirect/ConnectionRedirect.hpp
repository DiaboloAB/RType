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

        static void handleHiClient(mobs::Registry &registry, GameContext &gameContext, PacketDatas &packet)
        {
            LOG("ConnectionRedirect", "[HiClient packet] received");
        }

        static void handlePingClient(mobs::Registry &registry, GameContext &gameContext, PacketDatas &packet)
        {
            mobs::Registry::View view = registry.view<NetworkClient>();
            uint64_t pingTimestamp = packet.first->getPacketTimeStamp();

            for (auto &entity : view) {

                auto &networkC = view.get<NetworkClient>(entity);

                if (*networkC.client->getDirectionEndpoint() != packet.second) {
                    ERR_LOG("handleConnection", "Invalid sender of packets.");
                    return;
                }
                networkC.client->setLastPing(std::chrono::steady_clock::now());

                auto duration = std::chrono::steady_clock::now() - std::chrono::steady_clock::time_point(std::chrono::milliseconds(pingTimestamp));
                auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
                LOG("ConnectionRedirect", "[Ping packet] received, latence:" + std::to_string(duration_ms) + "ms.");
            }
        }

        static void handlePingRoom(mobs::Registry &registry, GameContext &gameContext, PacketDatas &packet)
        {
            mobs::Registry::View view = registry.view<NetworkRoom>();
            uint64_t pingTimestamp = packet.first->getPacketTimeStamp();

            for (auto &entity : view) {
                auto &networkC = view.get<NetworkRoom>(entity);

                networkC.room->resetPing(packet.second);
                auto duration = std::chrono::steady_clock::now() - std::chrono::steady_clock::time_point(std::chrono::milliseconds(pingTimestamp));
                auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
                LOG("ConnectionRedirect", "[Ping packet] received, latence:" + std::to_string(duration_ms) + "ms.");
            }
        }
};
} // namespace RType

#endif  // CONNECTIONREDIRECT_HPP
