/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#pragma once

#include "mobs/mobs.hpp"
#include "gameContext/GameContext.hpp"

namespace RType::Network {
class EntityRedirect {
    private:
        using PacketDatas = std::pair<std::shared_ptr<dimension::APacket>, asio::ip::udp::endpoint>;

    public:
        static void create(mobs::Registry &registry, GameContext &gameContext, PacketDatas &packet)
        {
            std::cerr << "Bonjour from create" << std::endl;
        };

        static void destroy(mobs::Registry &registry, GameContext &gameContext, PacketDatas &packet)
        {
            std::cerr << "Bonjour from destroy" << std::endl;
        };

        static void move(mobs::Registry &registry, GameContext &gameContext, PacketDatas &packet)
        {
            std::cerr << "Bonjour from move" << std::endl;
        };
};
}