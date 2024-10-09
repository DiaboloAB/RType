/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef ANIMPLAYER_HPP
#define ANIMPLAYER_HPP

#include "common/ICppScript.hpp"
#include "gameContext/GameContext.hpp"

namespace RType
{

class AnimPlayerScript : public RType::ICppScript
{
   public:
    void update(mobs::Registry &registry, GameContext &gameContext) override
    {
        int speed = 300;
        if (gameContext._runtime->getKeyDown(KeyCode::UpArrow))
        {
            Animations &animations = registry.get<Animator>(_entity).animations;
            animations.playAnim("up");
        }
        if (gameContext._runtime->getKeyUp(KeyCode::UpArrow))
        {
            Animations &animations = registry.get<Animator>(_entity).animations;
            animations.playAnim("default");
        }
        if (gameContext._runtime->getKeyDown(KeyCode::DownArrow))
        {
            Animations &animations = registry.get<Animator>(_entity).animations;
            animations.playAnim("down");
        }
        if (gameContext._runtime->getKeyUp(KeyCode::DownArrow))
        {
            Animations &animations = registry.get<Animator>(_entity).animations;
            animations.playAnim("default");
        }
    }
    void setEntity(mobs::Entity entity) override { _entity = entity; }

   private:
    mobs::Entity _entity;
};

}  // namespace RType

#endif  // ANIMPLAYER_HPP