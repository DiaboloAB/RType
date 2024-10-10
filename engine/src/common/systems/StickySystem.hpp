/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef STICKYSYSTEM_H
#define STICKYSYSTEM_H

#include <common/components.hpp>
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
        auto view = registry.view<Basics, Transform>();
        auto view2 = registry.view<Sticky, Transform>();

        for (auto entity : view2)
        {
            Sticky &sticky = registry.get<Sticky>(entity);
            for (auto entity2 : view)
            {
                if (entity == entity2)
                {
                    continue;
                }
                auto &basic = registry.get<Basics>(entity2);
                if (basic.tag == sticky.target)
                {
                    auto &transform = registry.get<Transform>(entity);
                    auto &transform2 = registry.get<Transform>(entity2);
                    transform.position = transform2.position + sticky.offset;
                    break;
                }
            }
        }
    }
   private:
    // Member variables
};

}  // namespace RType

#endif  // STICKYSYSTEM_H