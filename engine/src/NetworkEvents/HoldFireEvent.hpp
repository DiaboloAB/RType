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
 * @class HoldFireEvent
 *
 * @brief Class used to manage in-game entities when a HOLD_SHOOT
 * event is received by the server.
 */
class HoldFireEvent
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
        return;
    }

    /**
     * @brief Notifies clients that a client has created a charged bullet. Sends the updated bullet
     * information to ensure that other clients recognize and handle the charged bullet
     * appropriately.
     *
     * @param sender: Sender endpoint of the game event.
     * @param registry: Entity-component registry.
     * @param gameContext: Context for managing the game state.
     * @param idHandler: Network id handler
     */
    static void update(asio::ip::udp::endpoint &sender, mobs::Registry &registry,
                       GameContext &gameContext, NetworkIdHandler &idHandler)
    {
        return;
    }
};
}  // namespace RType::Network
