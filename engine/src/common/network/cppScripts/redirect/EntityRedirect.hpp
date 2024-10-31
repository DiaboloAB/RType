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
            try {
                auto packetCreate = std::dynamic_pointer_cast<dimension::CreateEntity>(packet.first);
                uint64_t currentTime = std::chrono::duration_cast<std::chrono::seconds>(
                               std::chrono::system_clock::now().time_since_epoch()).count();
                if (packetCreate->getPacketTimeStamp() + 2 >= currentTime)
                    return;
                mobs::Entity entity = gameContext._sceneManager.instantiate(packetCreate->getEntityToCreate(), gameContext);
                auto &transform = registry.get<Transform>(entity);
                transform.position.x = packetCreate->getPosX();
                transform.position.y = packetCreate->getPosY();
                auto &networkData = registry.get<NetworkData>(entity);
                networkData._id = packetCreate->getNetworkId();
                LOG("EntityRedirect", "Entity created. {Network id: " + std::to_string(networkData._id) + "}");
            } catch (std::exception &e) {
                ERR_LOG("EntityRedirect", std::string("create {") + e.what() + "}");
            }
        };

        static void destroy(mobs::Registry &registry, GameContext &gameContext, PacketDatas &packet)
        {
            try {
                auto packetDestroy = std::dynamic_pointer_cast<dimension::DestroyEntity>(packet.first);
                uint64_t currentTime = std::chrono::duration_cast<std::chrono::seconds>(
                               std::chrono::system_clock::now().time_since_epoch()).count();
                if (packetDestroy->getPacketTimeStamp() + 2 >= currentTime)
                    return;
                mobs::Registry::View view = registry.view<NetworkData>();
                uint32_t idToDestroy = packetDestroy->getNetworkId(); 
                for (auto &entity : view) {
                    auto &networkData = registry.get<NetworkData>(entity);
                    if (networkData._id == idToDestroy) {
                        registry.kill(entity);
                        LOG("EntityRedirect", std::string("Entity destroyed {Network id: ") +
                            std::to_string(idToDestroy) + "}");
                        return;
                    }
                }

            } catch (std::exception &e) {
                ERR_LOG("EntityRedirect" , std::string("destroy {") + e.what() + "}");
            }
        };

        static void move(mobs::Registry &registry, GameContext &gameContext, PacketDatas &packet)
        {
            std::cerr << "Bonjour from move" << std::endl;
        };
};
}