/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#pragma once

#include "ClientEventType.hpp"
#include "gameContext/GameContext.hpp"
#include "mobs/mobs.hpp"

namespace RType::Network
{
class EventRedirect
{
   private:
    using PacketDatas = std::pair<std::shared_ptr<dimension::APacket>, asio::ip::udp::endpoint>;

   public:

    /**
     * @brief Send to client entities to create when someone's connecting.
     *
     * @param registry: Reference to the entity-component registry.
     * @param gameContext: Reference to the game context.
     * @param packet: Update packet data & endpoint of packet sender.
     */
    static void sendNewConnection(mobs::Registry &registry, GameContext &gameContext,
                                  PacketDatas &packet, NetworkRoom &roomComp)
    {
        uint32_t idNewPlayer = roomComp.idFactory.generateNetworkId();
        std::unordered_map<asio::ip::udp::endpoint, uint32_t> connectedId =
            roomComp.room->getIdMap();
        auto updateScene = roomComp.factory.createEmptyPacket<dimension::UpdateEntity>();
        updateScene->setNetworkId(0);
        updateScene->setDescription("scene:multiplayer");
        roomComp.room->send(updateScene, packet.second);
        auto createPacketAlly = roomComp.factory.createEmptyPacket<dimension::CreateEntity>();
        createPacketAlly->setNetworkId(idNewPlayer);
        createPacketAlly->setEntityToCreate("ally");
        createPacketAlly->setPosX(100);
        createPacketAlly->setPosY((connectedId.size() + 1) * 150);
        createPacketAlly->setScaleX(1);
        createPacketAlly->setScaleY(1);
        for (auto &endp : roomComp.room->getIdMap())
            roomComp.room->send(createPacketAlly, endp.first);
        int counter = 1;
        for (auto &endp : roomComp.room->getIdMap())
        {
            auto createPacket = roomComp.factory.createEmptyPacket<dimension::CreateEntity>();
            createPacket->setNetworkId(endp.second);
            createPacket->setEntityToCreate("ally");
            createPacket->setPosX(100);
            createPacket->setPosY(counter * 150);
            createPacket->setScaleX(1);
            createPacket->setScaleY(1);
            roomComp.room->send(createPacket, packet.second);
            counter++;
        }
        auto entity = gameContext._sceneManager.instantiate("ally", gameContext);
        auto &networkC = registry.get<NetworkData>(entity);
        auto &transform = registry.get<Transform>(entity);
        networkC._id = idNewPlayer;
        transform.position.x = 100;
        transform.position.y = (connectedId.size() + 1) * 150;
        auto createPacketPlayer = roomComp.factory.createEmptyPacket<dimension::CreateEntity>();
        createPacketPlayer->setNetworkId(idNewPlayer);
        createPacketPlayer->setEntityToCreate("player");
        createPacketPlayer->setPosX(transform.position.x);
        createPacketPlayer->setPosY(transform.position.y);
        createPacketPlayer->setScaleX(1);
        createPacketPlayer->setScaleY(1);
        roomComp.room->send(createPacketPlayer, packet.second);
        roomComp.room->addSenderToRoom(packet.second, idNewPlayer);
        LOG("EventRedirect", "Client init in game");
    }

    /**
     * @brief Handler of Events packet into the ECS from room side.
     *
     * @param registry: Reference to the entity-component registry.
     * @param gameContext: Reference to the game context.
     * @param packet: Update packet data & endpoint of packet sender.
     */
    static void handleEvent(mobs::Registry &registry, GameContext &gameContext, PacketDatas &packet)
    {
        try
        {
            mobs::Registry::View view = registry.view<NetworkRoom>();
            auto &networkC = view.get<NetworkRoom>(view.front());
            auto event = std::dynamic_pointer_cast<dimension::ClientEvent>(packet.first);
            if (dimension::ClientEventType::ROOM == event->getClientEvent())
            {
                std::string description = event->getDescription();
                size_t pos = description.find('=');
                if (pos == std::string::npos || description.substr(0, pos) != "join")
                {
                    ERR_LOG("EventRedirect", "Unkown event {" + description + "}");
                    return;
                }
                if (networkC.room->getCode() != description.substr(pos + 1))
                {
                    ERR_LOG("EventRedirect", "Invalid code.");
                    return;
                }
                sendNewConnection(registry, gameContext, packet, networkC);
            }
            else
            {
                return gameEvent(registry, gameContext, packet);
            }
        }
        catch (std::exception &e)
        {
            ERR_LOG("EventRedirect", e.what());
        }
    }

    /**
     * @brief Handle events links to game in room.
     *
     * @param registry: Reference to the entity-component registry.
     * @param gameContext: Reference to the game context.
     * @param packet: Update packet data & endpoint of packet sender.
     */
    static void gameEvent(mobs::Registry &registry, GameContext &gameContext, PacketDatas &packet)
    {
        auto event = std::dynamic_pointer_cast<dimension::ClientEvent>(packet.first);

        if (dimension::ClientEventType::ATTACK == event->getClientEvent())
        {
            std::string description = event->getDescription();

            if (description.find("laser:shoot") != std::string::npos)
            {
                handleLaser(registry, gameContext, packet);
                return;
            }
            return;
        }
        return;
    }

    /**
     * @brief Handler of player shoot.
     *
     * @param registry: Reference to the entity-component registry.
     * @param gameContext: Reference to the game context.
     * @param packet: Update packet data & endpoint of packet sender.
     */
    static void handleLaser(mobs::Registry &registry, GameContext &gameContext, PacketDatas &packet)
    {
        auto event = std::dynamic_pointer_cast<dimension::ClientEvent>(packet.first);
        auto description = event->getDescription();

        size_t firstEqual = description.find('=');
        size_t secondEqual = description.find('=', firstEqual + 1);
        std::string laserSize = description.substr(firstEqual + 1, secondEqual - firstEqual - 1);
        std::string playerId = description.substr(description.find_last_of('=') + 1, description.size());
        std::string prefabName = "Laser";

        if (laserSize == "medium") {
            prefabName = "LaserMedium";
        } else if (laserSize == "large") {
            prefabName = "LaserLarge";
        } else if (laserSize == "full") {
            prefabName = "LaserFull";
        }

        mobs::Entity laser = gameContext._sceneManager.instantiate(prefabName, gameContext);

        auto view = registry.view<Basics, NetworkData>();

        for (auto entity : view)
        {
            auto &networkData = registry.get<NetworkData>(entity);
            if (std::to_string(networkData._id) == playerId)
            {
                auto &transform = registry.get<Transform>(entity);
                auto &laserTransform = registry.get<Transform>(laser);
                auto &laserNetworkData = registry.get<NetworkData>(laser);

                NetworkRoom &room = registry.get<NetworkRoom>(registry.view<NetworkRoom>().front());
                uint32_t networkId = room.idFactory.generateNetworkId();

                laserTransform.position = transform.position + mlg::vec3(50, 0, 0);
                laserNetworkData._id = networkId;
                sendLaserSpawn(registry, prefabName, laserTransform.position, laserNetworkData._id, registry.get<NetworkRoom>(registry.view<NetworkRoom>().front()));
            }
        }
    }

    /**
     * @brief Send laser to create to clients.
     *
     * @param registry: Reference to the entity-component registry.
     * @param prefab: Entity to create.
     * @param position: Position at creation.
     * @param networkId: Id of the entity.
     * @param room: Reference to room component.
     */
    static void sendLaserSpawn(mobs::Registry &registry, std::string prefab, mlg::vec3 position, uint32_t networkId, NetworkRoom &room)
    {
        auto spawnServe = room.factory.createEmptyPacket<dimension::CreateEntity>();

        spawnServe->setNetworkId(networkId);
        spawnServe->setEntityToCreate(prefab);
        spawnServe->setPosX(position.x);
        spawnServe->setPosY(position.y);
        spawnServe->setScaleX(1);
        spawnServe->setScaleY(1);

        room.room->sendToAll(spawnServe);
    }
};
}  // namespace RType::Network
