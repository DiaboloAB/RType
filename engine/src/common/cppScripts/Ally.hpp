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

class Ally : public RType::ICppScript
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
            auto &transform = registry.get<Transform>(getEntity());
            auto networkPosition = std::get<mlg::vec3>(args[0]);
            auto networdDirection = std::get<mlg::vec3>(args[1]);

            transform.position = networkPosition;
            _direction += networdDirection;
            
        } else if (action == "setDirection")
        {
            auto networdDirection = std::get<mlg::vec3>(args[0]);
            auto &transform = registry.get<Transform>(getEntity());

            _direction += networdDirection;
        }
    }

    static constexpr const char *name = "Ally";

   private:
    mlg::vec3 _direction = mlg::vec3(0, 0, 0);

};

}  // namespace RType

#endif  // ALLY_HPP