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

class MovePlayer : public RType::ICppScript
{
   public:
    int speed = 600;

    void update(mobs::Registry &registry, GameContext &gameContext) override
    {
        auto &transform = registry.get<Transform>(getEntity());
        auto &hitbox = registry.get<Hitbox>(getEntity());

        if (gameContext._runtime->getKeyDown(KeyCode::UpArrow))
        {
            _direction = _direction + mlg::vec3(0, -1, 0);
        }
        if (gameContext._runtime->getKeyDown(KeyCode::DownArrow))
        {
            _direction = _direction + mlg::vec3(0, 1, 0);
        }
        if (gameContext._runtime->getKeyDown(KeyCode::RightArrow))
        {
            _direction = _direction + mlg::vec3(1, 0, 0);
        }
        if (gameContext._runtime->getKeyDown(KeyCode::LeftArrow))
        {
            _direction = _direction + mlg::vec3(-1, 0, 0);
        }

        if (gameContext._runtime->getKeyUp(KeyCode::UpArrow))
        {
            _direction = _direction - mlg::vec3(0, -1, 0);
        }
        if (gameContext._runtime->getKeyUp(KeyCode::DownArrow))
        {
            _direction = _direction - mlg::vec3(0, 1, 0);
        }
        if (gameContext._runtime->getKeyUp(KeyCode::RightArrow))
        {
            _direction = _direction - mlg::vec3(1, 0, 0);
        }
        if (gameContext._runtime->getKeyUp(KeyCode::LeftArrow))
        {
            _direction = _direction - mlg::vec3(-1, 0, 0);
        }

        transform.position += _direction * speed * gameContext._deltaT;
        // TODO: block the player in the screen
    }

    static constexpr const char *name = "MovePlayer";

   private:
    mlg::vec3 _direction = mlg::vec3(0, 0, 0);
};

}  // namespace RType

#endif  // MOVEPLAYER_HPP