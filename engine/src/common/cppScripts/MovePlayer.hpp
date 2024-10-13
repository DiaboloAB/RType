/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef MOVEPLAYER_HPP
#define MOVEPLAYER_HPP

#include "common/ICppScript.hpp"
#include "gameContext/GameContext.hpp"

namespace RType
{

class MovePlayerScript : public RType::ICppScript
{
   public:
    void update(mobs::Registry &registry, GameContext &gameContext) override
    {
        if (!gameContext._networkHandler || gameContext._networkHandler->getIsServer()) return;
        if (gameContext._runtime->getKeyDown(KeyCode::UpArrow))
        {
            gameContext._networkHandler->sendToAll(Network::ClientEventPacket(Network::MOVE_UP));
        }
        if (gameContext._runtime->getKeyDown(KeyCode::DownArrow))
        {
            gameContext._networkHandler->sendToAll(Network::ClientEventPacket(Network::MOVE_DOWN));
        }
        if (gameContext._runtime->getKeyDown(KeyCode::LeftArrow))
        {
            gameContext._networkHandler->sendToAll(Network::ClientEventPacket(Network::MOVE_LEFT));
        }
        if (gameContext._runtime->getKeyDown(KeyCode::RightArrow))
        {
            gameContext._networkHandler->sendToAll(Network::ClientEventPacket(Network::MOVE_RIGHT));
        }
        if (gameContext._runtime->getKeyUp(KeyCode::UpArrow))
        {
            gameContext._networkHandler->sendToAll(
                Network::ClientEventPacket(Network::STOP_MOVE_UP));
        }
        if (gameContext._runtime->getKeyUp(KeyCode::DownArrow))
        {
            gameContext._networkHandler->sendToAll(
                Network::ClientEventPacket(Network::STOP_MOVE_DOWN));
        }
        if (gameContext._runtime->getKeyUp(KeyCode::LeftArrow))
        {
            gameContext._networkHandler->sendToAll(
                Network::ClientEventPacket(Network::STOP_MOVE_LEFT));
        }
        if (gameContext._runtime->getKeyUp(KeyCode::RightArrow))
        {
            gameContext._networkHandler->sendToAll(
                Network::ClientEventPacket(Network::STOP_MOVE_RIGHT));
        }
    }
    void setEntity(mobs::Entity entity) override { _entity = entity; }

   private:
    mobs::Entity _entity;
};

}  // namespace RType

#endif  // MOVEPLAYER_HPP