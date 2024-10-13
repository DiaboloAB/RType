/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef DRAWABLESYSTEM_H
#define DRAWABLESYSTEM_H

#include <system/ISystem.hpp>

#include "common/components.hpp"
// std

namespace RType
{

class DrawableSystem : public ISystem
{
   public:
    DrawableSystem() {}
    ~DrawableSystem() {}

    void draw(mobs::Registry &registry, GameContext &gameContext) override
    {
        auto view = registry.view<Text, Transform>();
        for (auto entity : view)
        {
            auto &text = view.get<Text>(entity);
            auto &transform = view.get<Transform>(entity);
            gameContext._runtime->drawText(text.font, text.text, transform.position, text.fontSize,
                                           text.color);
        }

        auto view2 = registry.view<Paragraph, Transform>();
        for (auto entity : view2)
        {
            auto &paragraph = view2.get<Paragraph>(entity);
            auto &transform = view2.get<Transform>(entity);
            int i = 0;
            for (auto line : paragraph.lines)
            {
                gameContext._runtime->drawText(
                    paragraph.font, line,
                    mlg::vec3(transform.position.x, transform.position.y + i, transform.position.z),
                    paragraph.fontSize, paragraph.color, true);
                i += paragraph.fontSize + 5;
            }
        }
    }
    // Getters

    // Setters

   private:
    // Member variables
};

}  // namespace RType

#endif  // DRAWABLESYSTEM_H