/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef STICKYSYSTEM_H
#define STICKYSYSTEM_H

#include <system/ISystem.hpp>
// std

namespace RType
{

class StickySystem : public ISystem
{
   public:
    StickySystem() {}
    ~StickySystem() {}

    void update(mobs::Registry &registry, GameContext &gameContext) override
    {
        auto view = registry.view<Sticky, Transform>();
        auto viewTarget = registry.view<Basics, Transform>();

        for (auto entity : view)
        {
            bool found = false;
            auto &sticky = view.get<Sticky>(entity);
            auto &transform = view.get<Transform>(entity);

            for (auto target : viewTarget)
            {
                auto &basic = viewTarget.get<Basics>(target);
                auto &targetTransform = viewTarget.get<Transform>(target);
                if (basic.tag == sticky.target)
                {
                    transform.position = targetTransform.position + sticky.offset * transform.scale;
                    found = true;
                    break;
                }
            }
            if (!found)
                registry.kill(entity);
        }
    }

   private:
    // Member variables
};

}  // namespace RType

#endif  // SPRITESYSTEM_H