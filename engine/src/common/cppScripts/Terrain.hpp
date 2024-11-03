/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include "common/ICppScript.hpp"
#include "gameContext/GameContext.hpp"

namespace RType
{

class Terrain : public RType::ICppScript
{
   public:
    void setScrolling(bool scrolling) { this->scrolling = scrolling; }

    void onCollisionEnter(mobs::Registry &registry, GameContext &gameContext, mobs::Entity other) override
    {
        NetworkRoom &room = registry.get<NetworkRoom>(registry.view<NetworkRoom>().front());
        auto killServe = room.factory.createEmptyPacket<dimension::DestroyEntity>();
        killServe->setNetworkId(registry.get<NetworkData>(other)._id);
        room.room->sendToAll(killServe);
        registry.kill(other);
    }

    void update(mobs::Registry &registry, GameContext &gameContext) override
    {
        int speed = 50;

        auto &transform = registry.get<Transform>(getEntity());

        if (scrolling)
        {
            transform.position.x -= speed * gameContext._deltaT;

            try {
            auto &networkC = gameContext.get<NetworkClient>("NetworkCom");

            if (networkC.client->_serverEndpoint) {
                return;
            }
            } catch (const std::exception &e) {
            }
            if (transform.position.x < -400)
            {
                NetworkRoom &room = registry.get<NetworkRoom>(registry.view<NetworkRoom>().front());
                auto killServe = room.factory.createEmptyPacket<dimension::DestroyEntity>();
                killServe->setNetworkId(registry.get<NetworkData>(getEntity())._id);
                room.room->sendToAll(killServe);

                registry.kill(getEntity());
            }
        }
    }

    static constexpr const char *name = "Terrain";

   private:
    bool scrolling = true;
};

}  // namespace RType

#endif  // TERRAIN_HPP