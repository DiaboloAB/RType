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

    void update(mobs::Registry &registry, GameContext &gameContext) override
    {
        int speed = 50;

        auto &transform = registry.get<Transform>(getEntity());

        if (scrolling)
        {
            transform.position.x -= speed * gameContext._deltaT;

            /// TODO : server responsability
            if (transform.position.x < -400)
            {
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