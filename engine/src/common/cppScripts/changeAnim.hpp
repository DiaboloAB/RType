/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef CHANGEANIM_H
#define CHANGEANIM_H

#include "common/ICppScript.hpp"
#include "gameContext/GameContext.hpp"

namespace RType
{

class ChangeAnimScript : public RType::ICppScript
{
   public:
    void update(mobs::Registry &registry, GameContext &gameContext) override
    {
        if (gameContext._runtime->getKeyDown(KeyCode::P))
        {
            auto viewAnim = registry.view<Transform, Animator, Basics>();
            for (auto entity : viewAnim)
            {
                Basics &basics = viewAnim.get<Basics>(entity);
                if (basics.tag != "entity1") continue;
                Animations &animations = viewAnim.get<Animator>(entity).animations;
                animations.playAnim("running");
            }
        }
    }
    void setEntity(mobs::Entity entity) override { _entity = entity; }

   private:
    mobs::Entity _entity;
};

}  // namespace RType

#endif  // CHANGEANIM_H