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

namespace RType::Network {
    class EventRedirect {
        private:
            using PacketDatas = std::pair<std::shared_ptr<dimension::APacket>, asio::ip::udp::endpoint>;
        public:
            static void sendNewConnection(mobs::Registry &registry, GameContext &gameContext, PacketDatas &packet,
            NetworkRoom &roomComp) 
            {
                uint32_t idNewPlayer = roomComp.idFactory.generateNetworkId();
                std::unordered_map<asio::ip::udp::endpoint, uint32_t> connectedId = roomComp.room->getIdMap();
                auto updateScene = roomComp.factory.createEmptyPacket<dimension::UpdateEntity>();
                updateScene->setNetworkId(0);
                updateScene->setDescription("scene:scene3");
                roomComp.room->send(updateScene, packet.second);
                auto createPacketAlly = roomComp.factory.createEmptyPacket<dimension::CreateEntity>();
                createPacketAlly->setNetworkId(idNewPlayer);
                createPacketAlly->setEntityToCreate("player");
                createPacketAlly->setPosX(100);
                createPacketAlly->setPosY((connectedId.size() + 1) * 150);
                for (auto &endp : connectedId)
                    roomComp.room->send(createPacketAlly, endp.first);
                int counter = 1;
                for (auto &endp : connectedId) {
                    auto createPacket = roomComp.factory.createEmptyPacket<dimension::CreateEntity>();
                    createPacket->setNetworkId(endp.second);
                    createPacket->setEntityToCreate("player");
                    createPacket->setPosX(100);
                    createPacket->setPosY(counter * 150);
                    roomComp.room->send(createPacket, endp.first);
                    counter++;
                }
                auto createPacketPlayer = roomComp.factory.createEmptyPacket<dimension::CreateEntity>();
                createPacketPlayer->setNetworkId(idNewPlayer);
                createPacketPlayer->setEntityToCreate("player");
                createPacketPlayer->setPosX(100);
                createPacketPlayer->setPosY((connectedId.size() + 1) * 150);
                roomComp.room->send(createPacketPlayer, packet.second);
                roomComp.room->addSenderToRoom(packet.second, idNewPlayer);
                LOG("EventRedirect", "Client init in game");
            }


            static void handleEvent(mobs::Registry &registry, GameContext &gameContext, PacketDatas &packet)
            {
                try {
                    mobs::Registry::View view = registry.view<NetworkRoom>();
                    auto &networkC = view.get<NetworkRoom>(view.front());
                    auto event = std::dynamic_pointer_cast<dimension::ClientEvent>(packet.first);
                    if (dimension::ClientEventType::ROOM == event->getClientEvent()) {
                        std::string description = event->getDescription();
                        size_t pos = description.find('=');
                        if (pos == std::string::npos || description.substr(0, pos) != "join") {
                            ERR_LOG("EventRedirect", "Unkown event {" + description + "}");
                            return;
                        }
                        if (networkC.room->getCode() != description.substr(pos + 1)) {
                            ERR_LOG("EventRedirect", "Invalid code.");
                            return;
                        }
                        sendNewConnection(registry, gameContext, packet, networkC);
                    } else {
                        return gameEvent(registry, gameContext, packet);
                    }
                } catch (std::exception &e) {
                    ERR_LOG("EventRedirect", e.what());
                }
            }

            static void gameEvent(mobs::Registry &registry, GameContext &gameContext, PacketDatas &packet)
            {
                LOG("EventRedirect", "Game event received");
                return;
            }
    };
}
