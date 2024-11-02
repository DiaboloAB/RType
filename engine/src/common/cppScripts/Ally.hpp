/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef ALLY_HPP
#define ALLY_HPP

#include "common/ICppScript.hpp"
#include "gameContext/GameContext.hpp"

namespace RType
{

class MovePlayer : public RType::ICppScript
{
   public:
    int speed = 600;

    void update(mobs::Registry &registry, GameContext &gameContext) override
    {
        auto &transform = registry.get<Transform>(getEntity());

        transform.position += _direction * speed * gameContext._deltaT;
    }

    void onButtonPressed(
        mobs::Registry &registry, GameContext &gameContext, std::string action,
        const std::vector<std::variant<mlg::vec3, int, std::string>> &args) override
    {
        if (action == "move" && args.size() >= 2)
        {
            auto position = std::get<mlg::vec3>(args[0]);
            auto direction = std::get<mlg::vec3>(args[1]);

            setPosition(registry, position);
            setDirection(direction);
        }
    }

    static constexpr const char *name = "MovePlayer";

   private:
    mlg::vec3 _direction = mlg::vec3(0, 0, 0);

    void setPosition(mobs::Registry &registry, mlg::vec3 NewPosition)
    {
        auto &transform = registry.get<Transform>(getEntity());

        transform.position = NewPosition;
    }

    void setDirection(mlg::vec3 NewDirection)
    {
        _direction += NewDirection;
    }
};

}  // namespace RType

#endif  // ALLY_HPP