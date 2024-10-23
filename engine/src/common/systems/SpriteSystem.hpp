/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef SPRITESYSTEM_H
#define SPRITESYSTEM_H

#include <system/ISystem.hpp>
// std

namespace RType
{

class SpriteSystem : public ISystem
{
   public:
    SpriteSystem() {}
    ~SpriteSystem() {}

    void load(mobs::Registry &registry, GameContext &gameContext) override
    {
        auto view = registry.view<Sprite>();
        for (auto entity : view)
        {
            auto &sprite = view.get<Sprite>(entity);
            sprite.id = gameContext._runtime->loadSprite(sprite.filePath);
        }

        auto viewAnim = registry.view<Animator>();
        for (auto entity : viewAnim)
        {
            AnimationList &animations = viewAnim.get<Animator>(entity).animations;
            for (auto &anim : animations.animations)
            {
                gameContext._runtime->loadSprite(anim.getFilePath());
            }
        }
    }

    void draw(mobs::Registry &registry, GameContext &gameContext) override
    {
        std::vector<std::tuple<mobs::Entity, Transform *, Sprite *>> entities;

        auto view = registry.view<Transform, Sprite>();

        for (auto entity : view)
        {
            auto &transform = view.get<Transform>(entity);
            auto &sprite = view.get<Sprite>(entity);

            entities.emplace_back(entity, &transform, &sprite);
        }

        std::sort(entities.begin(), entities.end(),
                  [this](const auto &lhs, const auto &rhs) { return compareZOrder(lhs, rhs); });

        for (const auto &entry : entities)
        {
            auto &transform = *std::get<1>(entry);
            auto &sprite = *std::get<2>(entry);

            gameContext._runtime->drawSprite(sprite.id, transform.position);
        }

        auto viewAnim = registry.view<Transform, Animator>();
        for (auto entity : viewAnim)
        {
            AnimationList &animations = viewAnim.get<Animator>(entity).animations;
            auto &transform = viewAnim.get<Transform>(entity);

            animations.time += gameContext._deltaT;
            Animation currentAnim = animations.getAnimation();
            float frameSpeed = 1.0f / currentAnim.getFrameSpeed();

            if (animations.time > frameSpeed)
            {
                animations.time = 0;
                animations.currentFrame += 1;
                if (animations.currentFrame >= currentAnim.getFrameCount())
                {
                    animations.currentFrame = 0;
                    if (!currentAnim.getLoop())
                    {
                        animations.playAnim("default");
                    }
                }
            }
            // gameContext._runtime->drawSprite(currentAnim.getFilePath(), transform.position,
            //                                  currentAnim.getSpriteCoords(animations.currentFrame),
            //                                  currentAnim.getScale(), currentAnim.getRotation());
        }
    }

   private:
    bool compareZOrder(const std::tuple<mobs::Entity, Transform *, Sprite *> &lhs,
                       const std::tuple<mobs::Entity, Transform *, Sprite *> &rhs) const
    {
        return std::get<1>(lhs)->position.z < std::get<1>(rhs)->position.z;
    }
    // Member variables
};

}  // namespace RType

#endif  // SPRITESYSTEM_H