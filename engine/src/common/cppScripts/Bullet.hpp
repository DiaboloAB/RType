/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef BULLET_HPP
#define BULLET_HPP

#include "common/ICppScript.hpp"
#include "gameContext/GameContext.hpp"

namespace RType
{

class Bullet : public RType::ICppScript
{
   public:
    void setDirection(const mlg::vec3 &direction) { this->direction = direction; }

    void update(mobs::Registry &registry, GameContext &gameContext) override
    {
        int speed = 500;

        auto &transform = registry.get<Transform>(getEntity());

        transform.position += direction * speed * gameContext._deltaT;
    }

    static constexpr const char *name = "Bullet";

   private:
    mlg::vec3 direction = mlg::vec3(0.0f);
};

}  // namespace RType

#endif  // BULLET_HPP