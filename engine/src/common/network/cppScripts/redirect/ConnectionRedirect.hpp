/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#pragma once

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
            LOG("ConnectionRedirect", "[Ping packet] received");
        }

        static void handlePingServer(mobs::Registry &registry, GameContext &gameContext, PacketDatas &packet)
        {
            LOG("ConnectionRedirect", "[Ping packet] received");
        }
};
} // namespace RType
