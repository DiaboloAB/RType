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
        if (!gameContext._networkHandler || gameContext._networkHandler->getIsServer())
            return;
        int speed = 600;
        if (gameContext._runtime->getKey(KeyCode::UpArrow))
        {
            gameContext._networkHandler->sendToAll(Network::ClientEventPacket(Network::MOVE_UP));
            //auto &transform = registry.get<Transform>(_entity);
            //if (transform.position.y < 0)
            //{
            //    transform.position.y = 0;
            //    return;
            //}
            //transform.position.y -= speed * gameContext._deltaT;
        }
        if (gameContext._runtime->getKey(KeyCode::DownArrow))
        {
            gameContext._networkHandler->sendToAll(Network::ClientEventPacket(Network::MOVE_DOWN));
            //auto &transform = registry.get<Transform>(_entity);
            //Hitbox &hitbox = registry.get<Hitbox>(_entity);
            //if (transform.position.y > 1080 - hitbox.size.y)
            //{
            //    transform.position.y = 1080 - hitbox.size.y;
            //    return;
            //}
            //transform.position.y += speed * gameContext._deltaT;
        }
        if (gameContext._runtime->getKey(KeyCode::LeftArrow))
        {
            gameContext._networkHandler->sendToAll(Network::ClientEventPacket(Network::MOVE_LEFT));
            // auto &transform = registry.get<Transform>(_entity);
            // if (transform.position.x < 0)
            // {
            //     transform.position.x = 0;
            //     return;
            // }
            // transform.position.x -= speed * gameContext._deltaT;
        }
        if (gameContext._runtime->getKey(KeyCode::RightArrow))
        {
            gameContext._networkHandler->sendToAll(Network::ClientEventPacket(Network::MOVE_RIGHT));
            // auto &transform = registry.get<Transform>(_entity);
            // auto &hitbox = registry.get<Hitbox>(_entity);
            // if (transform.position.x > 1920 - hitbox.size.x)
            // {
            //     transform.position.x = 1920 - hitbox.size.x;
            //     return;
            // }
            // transform.position.x += speed * gameContext._deltaT;
        }
    }
    void setEntity(mobs::Entity entity) override { _entity = entity; }

   private:
    mobs::Entity _entity;
};

}  // namespace RType

#endif  // MOVEPLAYER_HPP