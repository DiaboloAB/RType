/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#pragma once

#include <regex>

#include "ClientEventType.hpp"
#include "gameContext/GameContext.hpp"
#include "mobs/mobs.hpp"

namespace RType::Network
{

/**
 * @brief Class UpdateRedirect that store the static method to handle Update packets
 * from client side.
 */
class UpdateRedirect
{
   private:
    using PacketDatas = std::pair<std::shared_ptr<dimension::APacket>, asio::ip::udp::endpoint>;

    /**
     * @brief Handle Update packet with room context by connecting client to room.
     *
     * @param registry: Reference to the entity-component registry.
     * @param gameContext: Reference to the game context.
     * @param packet: Update packet data & endpoint of packet sender.
     */
    static void updateRoom(mobs::Registry &registry, GameContext &gameContext, PacketDatas &packet)
    {
        auto packetUpdate = std::dynamic_pointer_cast<dimension::UpdateEntity>(packet.first);
        mobs::Registry::View view = registry.view<NetworkClient>();

        std::string host;
        unsigned int port;
        std::string code;
        std::smatch matches;

        std::string packetDescription = packetUpdate->getDescription();
        const std::regex roomPattern(R"(^room:([^:]+):([^:]+):([^:]+)$)");

        if (std::regex_match(packetDescription, matches, roomPattern))
        {
            host = matches[1].str();
            port = std::stoi(matches[2].str());
            code = matches[3].str();
        }

        for (auto &entity : view)
        {
            auto &networkC = view.get<NetworkClient>(entity);

            if (*networkC.client->getDirectionEndpoint() != packet.second)
            {
                ERR_LOG("handleConnection", "Invalid sender of packets.");
                return;
            }
            try
            {
                networkC.client->connectDirectionEndpoint(host, port);
                if (networkC.client->_directionEndpoint == networkC.client->_serverEndpoint)
                    ERR_LOG("LA", "LA PUTAIN DE SA MERE");
                auto event = networkC.factory.createEmptyPacket<dimension::ClientEvent>();
                event->setClientEvent(dimension::ClientEventType::ROOM);
                event->setDescription("join=" + code);
                networkC.client->send(event, *networkC.client->_directionEndpoint);
                LOG("UpdateRedirect", "Direction endpoint set");
            }
            catch (std::exception &e)
            {
                ERR_LOG("UpdateRedirect", "Problem occured during join of room.");
            }
        }
    }

   static void updateScene(mobs::Registry &registry, GameContext &gameContext, PacketDatas &packet)
   {
        try {
            auto packetUpdate = std::dynamic_pointer_cast<dimension::UpdateEntity>(packet.first);
            std::string description = packetUpdate->getDescription();
            size_t pos = description.find(':');
            gameContext._sceneManager.switchScene(description.substr(pos + 1));
            LOG("UpdateRedirect", "Scene switched.");
        } catch (std::exception &e) {
            ERR_LOG("UpdateRedirect", e.what());
        }
   }

   public:
    /**
     * @brief Call the handler associated with Update packet context stored in
     * packet description.
     *
     * @param registry: Reference to the entity-component registry.
     * @param gameContext: Reference to the game context.
     * @param packet: Update packet data & endpoint of packet sender.
     */
    static void update(mobs::Registry &registry, GameContext &gameContext, PacketDatas &packet)
    {
        try
        {
            auto packetUpdate = std::dynamic_pointer_cast<dimension::UpdateEntity>(packet.first);
            uint64_t currentTime = std::chrono::duration_cast<std::chrono::seconds>(
                                       std::chrono::system_clock::now().time_since_epoch())
                                       .count();

            if (currentTime - packetUpdate->getPacketTimeStamp() >= 2) return;

            std::string packetDescription = packetUpdate->getDescription();
            if (packetDescription.find("room:", 0) == 0) updateRoom(registry, gameContext, packet);
            if (packetDescription.find("scene:", 0) == 0) updateScene(registry, gameContext, packet);
        }
        catch (std::exception &e)
        {
            ERR_LOG("UpdateRedirect", std::string("{") + e.what() + "}");
        }
    };
};
}  // namespace RType::Network
