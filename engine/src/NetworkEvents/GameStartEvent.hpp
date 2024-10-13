/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#pragma once

#include <NetworkHandler/NetworkIdHandler.hpp>
#include <asio.hpp>
#include <gameContext/GameContext.hpp>
#include <mobs/mobs.hpp>

namespace RType::Network
{
/**
 * @class GameStartEvent
 *
 * @brief Class used to manage in-game entities when a GAME_START
 * event is received by the server.
 */
class GameStartEvent
{
   public:
    /**
     * @brief Checks if the sender of this event is authorized to send it and
     * whether the receiver is the server.
     *
     * @param sender: Sender endpoint of the game event.
     * @param gameContext Context for managing the game state.
     * @return True if the sender is valid, False otherwise.
     */
    static bool checkSenderValidity(asio::ip::udp::endpoint &sender, GameContext &gameContext)
    {
        auto networkHandler = gameContext._networkHandler;
        if (!networkHandler || !networkHandler->getIsServer() ||
            networkHandler->getGameState() == IN_GAME)
            return false;
        auto endpointMap = networkHandler->getEndpointMap();
        auto senderData = endpointMap.find(sender);
        if (senderData == endpointMap.end() || !senderData->second.getConnected()) return false;
        return true;
    }

    /**
     * @brief Initializes server entities (allies for players) to assign network IDs to the created
     * entities. This information is used to notify clients about which entities to create: the
     * player if the network ID corresponds to theirs, or allies if it corresponds to others.
     *
     * Each client has a unique network ID to differentiate between them.
     *
     * @param endpointMap: Map corresponding to enpoints and their state in game.
     * @param registry: Entity-component registry.
     * @param gameContext: Context for managing the game state.
     * @param idHandler: Network id handler.
     * @return List of the created network ids.
     */
    static std::list<uint32_t> initServerEntities(
        std::map<asio::ip::udp::endpoint, RType::Network::EndpointState> &endpointMap,
        mobs::Registry &registry, GameContext &gameContext, NetworkIdHandler &idHandler)
    {
        float posX = 100.0;
        float posY = 100.0;
        std::list<uint32_t> connectedNid;

        for (auto &endpoint : endpointMap)
        {
            if (!endpoint.second.getConnected()) continue;
            mobs::Entity newEntity = gameContext._sceneManager.loadPrefab("ally.json", gameContext);
            auto &transform = registry.get<Transform>(newEntity);
            transform.position = mlg::vec3(posX, posY, 0.0f);
            auto &networkComp = registry.get<NetworkComp>(newEntity);
            networkComp.id = idHandler.generateNetworkId();
            endpoint.second.setNetworkId(networkComp.id);
            connectedNid.emplace_back(networkComp.id);
            if (posY >= 900)
            {
                posX += 100;
                posY = 100;
            }
            else
                posY += 100;
        }
        return connectedNid;
    }

    /**
     * @brief Sends the entities to be created to all clients. The player entity is sent if
     * it corresponds to their network ID; otherwise, allies are sent.
     *
     * @param endpointMap Map corresponding to endpoints and their states in the game.
     * @param connectedNid List of created network IDs associated with clients.
     * @param networkHandler Pointer to the network handler used to send packets to clients.
     */
    static void sendClientEntities(
        std::pair<const asio::ip::udp::endpoint, RType::Network::EndpointState> &endpoint,
        std::list<uint32_t> connectedNid,
        std::shared_ptr<RType::Network::NetworkHandler> networkHandler)
    {
        float posX = 100.0;
        float posY = 100.0;
        for (auto &nid : connectedNid)
        {
            if (nid == endpoint.second.getNetworkId())
                networkHandler->sendNewPacket(CreateEntityPacket(nid, posX, posY, "player.json"),
                                              endpoint.first);
            else
                networkHandler->sendNewPacket(CreateEntityPacket(nid, posX, posY, "ally.json"),
                                              endpoint.first);
            if (posY >= 900)
            {
                posX += 100;
                posY = 100;
            }
            else
                posY += 100;
        }
    }

    /**
     * @brief Notifies clients that the game has started by sending the entities (player and allies)
     * to be created for gameplay.
     *
     * @param sender: Sender endpoint of the game event.
     * @param registry: Entity-component registry.
     * @param gameContext: Context for managing the game state.
     * @param idHandler: Network id handler
     */
    static void update(asio::ip::udp::endpoint &sender, mobs::Registry &registry,
                       GameContext &gameContext, NetworkIdHandler &idHandler)
    {
        if (!checkSenderValidity(sender, gameContext)) return;
        auto networkHandler = gameContext._networkHandler;
        networkHandler->setGameState(IN_GAME);
        auto &endpointMap = networkHandler->getEndpointMap();
        std::list<uint32_t> connectedNid =
            initServerEntities(endpointMap, registry, gameContext, idHandler);
        for (auto &endpoint : endpointMap)
        {
            if (endpoint.second.getConnected())
                sendClientEntities(endpoint, connectedNid, networkHandler);
        }
    }
};
}  // namespace RType::Network
