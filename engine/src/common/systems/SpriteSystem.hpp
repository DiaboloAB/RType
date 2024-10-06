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

    void start(ECS::Registry &registry, GameContext &gameContext) override
    {
        auto view = registry.view<Sprite>();
        for (auto entity : view)
        {
            auto &sprite = view.get<Sprite>(entity);
            gameContext._runtime->loadSprite(sprite.filePath, sprite.filePath, sprite.filePath);
        }
    }

    void draw(ECS::Registry &registry, GameContext &gameContext) override
    {
        auto view = registry.view<Transform, Sprite>();
        for (auto entity : view)
        {
            auto &transform = view.get<Transform>(entity);
            auto &sprite = view.get<Sprite>(entity);
            // gameContext._runtime->drawSprite(sprite.filePath, transform.position.x,
            //                                  transform.position.y);
        }
    }

    // Getters

    // Setters

   private:
    // Member variables
};

}  // namespace RType

#endif  // SPRITESYSTEM_H