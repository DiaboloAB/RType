/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#pragma once

#include <NetworkEvents/GameStartEvent.hpp>
#include <NetworkEvents/MoveDownEvent.hpp>
#include <NetworkEvents/MoveLeftEvent.hpp>
#include <NetworkEvents/MoveRightEvent.hpp>
#include <NetworkEvents/MoveUpEvent.hpp>
#include <NetworkEvents/StopMoveDownEvent.hpp>
#include <NetworkEvents/StopMoveLeftEvent.hpp>
#include <NetworkEvents/StopMoveRightEvent.hpp>
#include <NetworkEvents/StopMoveUpEvent.hpp>
#include <NetworkHandler/NetworkIdHandler.hpp>
#include <NetworkPacketManager/ClientEventPacket.hpp>
#include <asio.hpp>
#include <functional>
#include <gameContext/GameContext.hpp>
#include <mobs/mobs.hpp>
#include <unordered_map>

namespace RType::Network
{
/**
 * @class NetworkEventHandler
 *
 * @brief Class used to invoke the update functions of event classes (e.g., MoveRightEvent, ...).
 * This class serves as the entry point for handling various game events.
 */
class NetworkEventHandler
{
   public:
    /**
     * @brief Constructor for the NetworkEventHandler class.
     * @param idHandler Reference to the idHandler used by various event classes to generate new
     * network IDs.
     */
    NetworkEventHandler(NetworkIdHandler &idHandler);

    ~NetworkEventHandler();

   public:
    /**
     * @brief Calls the update function of the event class associated with the event passed as
     * parameter.
     *
     * @param event Game event to handle.
     * @param sender Endpoint of the entity sending the event.
     * @param registry Entity-component registry.
     * @param gameContext Context for managing the game state.
     */
    void update(ClientEvent event, asio::ip::udp::endpoint &sender, mobs::Registry &registry,
                GameContext &gameContext);

   private:
    std::unordered_map<ClientEvent, std::function<void(asio::ip::udp::endpoint &, mobs::Registry &,
                                                       GameContext &, NetworkIdHandler &)>>
        _eventMap;
    NetworkIdHandler _idHandler;
};
}  // namespace RType::Network
