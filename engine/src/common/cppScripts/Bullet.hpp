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

        if (outOfBounds(transform.position))
        {
            registry.kill(getEntity());
        }
    }


    void onButtonPressed(mobs::Registry &registry, GameContext &gameContext,
                         std::string action, ...) override
    {
        if (action == "move")
        {
            va_list args;
            va_start(args, action);
            mlg::vec3 position = va_arg(args, mlg::vec3);
            mlg::vec3 direction = va_arg(args, mlg::vec3);

            checkPosition(registry, position, direction);
            
            va_end(args);
        }
    }

    static constexpr const char *name = "Bullet";

   private:
    mlg::vec3 direction = mlg::vec3(0.0f);

    bool outOfBounds(const mlg::vec3 &position)
    {
        return position.x < 0 || position.x > 1920 || position.y < 0 || position.y > 1080;
    }

    void checkPosition(mobs::Registry &registry, mlg::vec3 NewPosition, mlg::vec3 NewDirection)
    {
        auto &transform = registry.get<Transform>(getEntity());

        if (NewPosition != transform.position)
        {
            transform.position = NewPosition;
        }
        if (direction.x == 0 && direction.y == 0)
        {
            direction = NewDirection;
        }
    }
};

}  // namespace RType

#endif  // BULLET_HPP