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

    void load(mobs::Registry &registry, GameContext &gameContext) override
    {
        auto view = registry.view<Text>();
        for (auto entity : view)
        {
            auto &text = view.get<Text>(entity);
            text.font_id = gameContext._runtime->loadFont(text.font);
        }
    }

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

        auto view3 = registry.view<Button, Transform>();
        for (auto entity : view3)
        {
            auto &button = view3.get<Button>(entity);
            auto &transform = view3.get<Transform>(entity);
            mlg::vec3 mousePos = gameContext._runtime->getMousePosition();
            if (mousePos.x > transform.position.x &&
                mousePos.x < transform.position.x + button.size.x &&
                mousePos.y > transform.position.y &&
                mousePos.y < transform.position.y + button.size.y)
            {
                mlg::vec4 buttonRect(transform.position.x, transform.position.y, button.size.x,
                                     button.size.y);
                gameContext._runtime->drawRectangle(
                    buttonRect, gameContext._runtime->getKey(KeyCode::Mouse0), button.color);
                if (gameContext._runtime->getKey(KeyCode::Mouse0))
                {
                    try
                    {
                        gameContext.get<CppScriptComponent>(button.target)
                            .callAllFunctions(button.action, registry, gameContext);
                    }
                    catch (const std::exception &e)
                    {
                        std::cerr << "Error: " << e.what() << std::endl;
                    }
                }
            }
            gameContext._runtime->drawText(
                button.font, button.text,
                mlg::vec3(transform.position.x + button.size.x / 2 - 5,
                          transform.position.y + button.size.y / 2 - 5, 0),
                16, mlg::vec3(255, 255, 255), true);
            // gameContext._runtime->drawButton(button.text, transform.position, button.size,
            // button.color,
            //                                  button.textColor, button.fontSize);
        }
    }
    // Getters

    // Setters

   private:
    // Member variables
};

}  // namespace RType

#endif  // DRAWABLESYSTEM_H