/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef LASER_H
#define LASER_H

#include "common/ICppScript.hpp"
#include "gameContext/GameContext.hpp"

namespace RType
{

class MoveLaser : public RType::ICppScript
{
   public:

    void reduceHealth(mobs::Registry &registry, int n) 
    {
        health -= n;
        if (health <= 0)
        {
            NetworkRoom &room = registry.get<NetworkRoom>(registry.view<NetworkRoom>().front());
            auto killServe = room.factory.createEmptyPacket<dimension::DestroyEntity>();
            killServe->setNetworkId(registry.get<NetworkData>(getEntity())._id);
            room.room->sendToAll(killServe);

            registry.kill(getEntity());
        }
    }

    void start(mobs::Registry &registry, GameContext &gameContext) override
    {
        auto &basic = registry.get<Basics>(getEntity());

        if (basic.tag == "LaserMedium")
        {
            health = 2;
        }
        else if (basic.tag == "LaserLarge")
        {
            health = 3;
        }
        else if (basic.tag == "LaserFull")
        {
            health = 4;
        }
    }

    void update(mobs::Registry &registry, GameContext &gameContext) override
    {
        int speed = 1000;
        auto &transform = registry.get<Transform>(getEntity());
        transform.position.x += speed * gameContext._deltaT;

        try {
            auto &networkC = gameContext.get<NetworkClient>("NetworkCom");

            if (networkC.client->_serverEndpoint) {
                return;
            }
        } catch (const std::exception &e) {
        }
        if (transform.position.x > 2000)
        {
            NetworkRoom &room = registry.get<NetworkRoom>(registry.view<NetworkRoom>().front());
            auto killServe = room.factory.createEmptyPacket<dimension::DestroyEntity>();
            killServe->setNetworkId(registry.get<NetworkData>(getEntity())._id);
            room.room->sendToAll(killServe);

            registry.kill(getEntity());
        }
    }

    static constexpr const char *name = "MoveLaser";

   private:
    int health = 1;
    // Member variables
};

}  // namespace RType

#endif  // LASER_H