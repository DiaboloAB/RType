/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef PLAYERSHOOT_HPP
#define PLAYERSHOOT_HPP

#include "common/ICppScript.hpp"
#include "gameContext/GameContext.hpp"
#include "utils/Timer.hpp"

namespace RType
{

class PlayerShoot : public RType::ICppScript
{
   public:
    void update(mobs::Registry &registry, GameContext &gameContext) override
    {
        if (timer.getState())
        {
            timer.setTime(timer.getTime() + gameContext._deltaT);
        }
        if (gameContext._runtime->getKeyDown(KeyCode::Space))
        {
            timer.start();
        }
        if (gameContext._runtime->getKeyUp(KeyCode::Space))
        {
            float charge = timer.getTime();
            auto &networkC = gameContext.get<NetworkClient>("NetworkCom");
            auto networkId = registry.get<NetworkData>(getEntity())._id;
            auto laserPacket = networkC.factory.createEmptyPacket<dimension::ClientEvent>();

            laserPacket->setClientEvent(dimension::ClientEventType::ATTACK);
            std::string PlayerId = std::to_string(networkId);

            if (charge < 0.4)
            {
                laserPacket->setDescription("laser:shoot=small=" + PlayerId);
            }
            else if (charge < 1)
            {
                laserPacket->setDescription("laser:shoot=medium=" + PlayerId);
            }
            else if (charge < 1.6)
            {
                laserPacket->setDescription("laser:shoot=large=" + PlayerId);
            }
            else
            {
                laserPacket->setDescription("laser:shoot=full=" + PlayerId);
            }

            networkC.client->send(laserPacket, *networkC.client->_directionEndpoint, true);
            timer.reset();
            timer.stop();
        }
    }
    static constexpr const char *name = "PlayerShoot";

   private:
    Timer timer;
    int health = 1;
};

}  // namespace RType

#endif  // PLAYERSHOOT_HPP