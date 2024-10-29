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
        void update(mobs::Registry &registry, GameContext &gameContext) override
        {
            int speed = 1000;
            auto &transform = registry.get<Transform>(getEntity());
            transform.position.x += speed * gameContext._deltaT;

            if (transform.position.x > 2000)
            {
                registry.kill(getEntity());
            }
        }

    static constexpr const char *name = "MoveLaser";

    private:
    // Member variables
};

}  // namespace RType

#endif  // LASER_H