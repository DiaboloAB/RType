/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#pragma once

#include "gameContext/GameContext.hpp"
#include "mobs/mobs.hpp"

namespace RType::Network
{
class EntityRedirect
{
   private:
    using PacketDatas = std::pair<std::shared_ptr<dimension::APacket>, asio::ip::udp::endpoint>;

   public:
    /**
     * @brief Handler of CreateEntity packet into the ECS from client side.
     *
     * @param registry: Reference to the entity-component registry.
     * @param gameContext: Reference to the game context.
     * @param packet: Update packet data & endpoint of packet sender.
     */
    static void create(mobs::Registry &registry, GameContext &gameContext, PacketDatas &packet)
    {
        try
        {
            auto packetCreate = std::dynamic_pointer_cast<dimension::CreateEntity>(packet.first);
            uint64_t currentTime = std::chrono::duration_cast<std::chrono::seconds>(
                                       std::chrono::system_clock::now().time_since_epoch())
                                       .count();
            if (currentTime - packetCreate->getPacketTimeStamp() >= 2) return;
            ERR_LOG("Test", packetCreate->getEntityToCreate());
            mobs::Entity entity = gameContext._sceneManager.instantiate(
                packetCreate->getEntityToCreate(), gameContext);
            auto &transform = registry.get<Transform>(entity);
            transform.position.x = packetCreate->getPosX();
            transform.position.y = packetCreate->getPosY();
            transform.scale.x *= packetCreate->getScaleX();
            transform.scale.y *= packetCreate->getScaleY();
            auto &networkData = registry.get<NetworkData>(entity);
            networkData._id = packetCreate->getNetworkId();
            LOG("EntityRedirect",
                "Entity created. {Network id: " + std::to_string(networkData._id) + " " +
                    std::to_string(transform.position.x) + " " +
                    std::to_string(transform.position.y) + "}");
        }
        catch (std::exception &e)
        {
            ERR_LOG("EntityRedirect", std::string("create {") + e.what() + "}");
        }
    };

    /**
     * @brief Handler of DestroyEntity packet into the ECS from client side.
     *
     * @param registry: Reference to the entity-component registry.
     * @param gameContext: Reference to the game context.
     * @param packet: Update packet data & endpoint of packet sender.
     */
    static void destroy(mobs::Registry &registry, GameContext &gameContext, PacketDatas &packet)
    {
        try
        {
            auto packetDestroy = std::dynamic_pointer_cast<dimension::DestroyEntity>(packet.first);
            uint64_t currentTime = std::chrono::duration_cast<std::chrono::seconds>(
                                       std::chrono::system_clock::now().time_since_epoch())
                                       .count();
            if (currentTime - packetDestroy->getPacketTimeStamp() >= 2) return;
            mobs::Registry::View view = registry.view<NetworkData>();
            uint32_t idToDestroy = packetDestroy->getNetworkId();
            for (auto &entity : view)
            {
                auto &networkData = registry.get<NetworkData>(entity);
                if (networkData._id == idToDestroy)
                {
                    registry.kill(entity);
                    LOG("EntityRedirect", std::string("Entity destroyed {Network id: ") +
                                              std::to_string(idToDestroy) + "}");
                    return;
                }
            }
        }
        catch (std::exception &e)
        {
            ERR_LOG("EntityRedirect", std::string("destroy {") + e.what() + "}");
        }
    };

    /**
     * @brief Handler of MoveEntity packet into the ECS from client side.
     *
     * @param registry: Reference to the entity-component registry.
     * @param gameContext: Reference to the game context.
     * @param packet: Update packet data & endpoint of packet sender.
     */
    static void move(mobs::Registry &registry, GameContext &gameContext, PacketDatas &packet)
    {
        try
        {
            auto packetMove = std::dynamic_pointer_cast<dimension::MoveEntity>(packet.first);
            uint64_t currentTime = std::chrono::duration_cast<std::chrono::seconds>(
                                       std::chrono::system_clock::now().time_since_epoch())
                                       .count();
            if (currentTime - packetMove->getPacketTimeStamp() >= 2) return;
            mobs::Registry::View view = registry.view<NetworkData>();
            uint32_t idToMove = packetMove->getNetworkId();
            for (auto &entity : view)
            {
                auto &networkData = registry.get<NetworkData>(entity);
                if (networkData._id == idToMove)
                {
                    mlg::vec3 position(packetMove->getPosX(), packetMove->getPosY(), 0);
                    mlg::vec3 direction(packetMove->getDirectionX(), packetMove->getDirectionY(),
                                        0);
                    getCppScriptById<ICppScript>(entity, registry)->onButtonPressed(registry, gameContext, "move", {position, direction});
                    return;
                }
            }
        }
        catch (std::exception &e)
        {
            ERR_LOG("EntityRedirect", std::string("move {") + e.what() + "}");
        }
    };

    static void moveServer(mobs::Registry &registry, GameContext &gameContext, PacketDatas &packet) 
    {
        auto packetMove = std::dynamic_pointer_cast<dimension::MoveEntity>(packet.first);
        try
        {
            uint64_t currentTime = std::chrono::duration_cast<std::chrono::seconds>(
                                        std::chrono::system_clock::now().time_since_epoch())
                                        .count();
            if (currentTime - packetMove->getPacketTimeStamp() >= 2) return;
            mobs::Registry::View view = registry.view<NetworkData>();
            uint32_t idToMove = packetMove->getNetworkId();
            for (auto &entity : view) {
                auto &networkData = registry.get<NetworkData>(entity);
                if (networkData._id == idToMove)
                {
                    mlg::vec3 position(packetMove->getPosX(), packetMove->getPosY(), 0);
                    mlg::vec3 direction(packetMove->getDirectionX(), packetMove->getDirectionY(), 0);
                    getCppScriptById<ICppScript>(entity, registry)->onButtonPressed(
                        registry, gameContext, "setDirection", {direction});
                    break;
                }
            }
        } catch (std::exception &e) {
                ERR_LOG("EntityRedirect", std::string("move {") + e.what() + "}");
        }
        auto &room = registry.get<NetworkRoom>(registry.view<NetworkRoom>().front());
        auto moveServ = room.factory.createEmptyPacket<dimension::MoveEntity>();
        moveServ->setNetworkId(packetMove->getNetworkId());
        moveServ->setDirectionX(packetMove->getDirectionX());
        moveServ->setDirectionY(packetMove->getDirectionY());
        mobs::Registry::View viewNdata = registry.view<NetworkData>();
        for (auto &entity : viewNdata) {
            auto &networkData = registry.get<NetworkData>(entity);
            if (networkData._id == moveServ->getNetworkId()) {
                auto &transform = registry.get<Transform>(entity);
                moveServ->setPosX(transform.position.x);
                moveServ->setPosY(transform.position.y);
            }
        }
        room.room->sendToAll(moveServ);
    };
};
}  // namespace RType::Network