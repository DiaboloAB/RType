/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef DRAWABLESYSTEM_H
#define DRAWABLESYSTEM_H

#include <system/ISystem.hpp>

#include "common/components/uiComponents.hpp"
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
            text.font_id = gameContext._runtime->loadFont(gameContext._assetsPath + text.font);
        }

        int i = 0;

        auto viewButton = registry.view<Button>();
        for (auto entity : viewButton)
        {
            auto &button = viewButton.get<Button>(entity);
            button.font_id = gameContext._runtime->loadFont(gameContext._assetsPath + button.font);
            if (i++ == 0) button.selected = true;
        }

        keyboardSprite_id =
            gameContext._runtime->loadSprite(gameContext._assetsPath + "graphics/keyboard.png");
    }

    void update(mobs::Registry &registry, GameContext &gameContext) override
    {
        auto viewButton = registry.view<Button, Transform>();

        Button *selectedButton = nullptr;
        Transform *selectedTransform = nullptr;
        std::vector<std::pair<Button &, Transform &>> buttons;

        for (auto entity : viewButton)
        {
            auto &button = viewButton.get<Button>(entity);
            auto &transform = viewButton.get<Transform>(entity);
            buttons.emplace_back(button, transform);
            if (button.selected)
            {
                selectedButton = &button;
                selectedTransform = &transform;
            }
        }

        if (!selectedButton) return;

        if (selectedButton->input && gameContext._runtime->getKeyDown(KeyCode::Enter))
        {
            if (!selectedButton->virtualKeyboard)
            {
                selectedButton->virtualKeyboard = true;
                return;
            }
        }
        else if (!selectedButton->input && gameContext._runtime->getKeyDown(KeyCode::Enter))
        {
            buttonAction(registry, gameContext, *selectedButton);
        }

        if (selectedButton->virtualKeyboard)
        {
            if (gameContext._runtime->getKeyDown(KeyCode::Escape))
            {
                selectedButton->virtualKeyboard = false;
            }
        }

        if (selectedButton->virtualKeyboard)
        {
            if (gameContext._runtime->getKeyDown(KeyCode::UpArrow))
                selectedKey.y--;
            else if (gameContext._runtime->getKeyDown(KeyCode::DownArrow))
                selectedKey.y++;
            else if (gameContext._runtime->getKeyDown(KeyCode::LeftArrow))
                selectedKey.x--;
            else if (gameContext._runtime->getKeyDown(KeyCode::RightArrow))
                selectedKey.x++;
            selectedKey.x = (int)(selectedKey.x + 13) % 13;
            selectedKey.y = (int)(selectedKey.y + 4) % 4;
            if (gameContext._runtime->getKeyDown(KeyCode::Enter))
            {
                if (selectedKey.y == 3 && selectedKey.x == 1)
                {
                    selectedButton->content += " ";
                }
                else if (selectedKey.y == 3 && selectedKey.x == 2)
                {
                    if (selectedButton->content.size() > 0) selectedButton->content.pop_back();
                }
                else if (selectedKey.y == 3 && selectedKey.x == 3)
                {
                    selectedButton->virtualKeyboard = false;
                }
                else
                    selectedButton->content += keys[selectedKey.y * 13 + selectedKey.x];
            }
        }

        if (selectedButton->virtualKeyboard) return;

        moveSelection(registry, gameContext, selectedButton, selectedTransform, buttons);
    }
    void draw(mobs::Registry &registry, GameContext &gameContext) override
    {
        auto view = registry.view<Text, Transform>();
        for (auto entity : view)
        {
            auto &text = view.get<Text>(entity);
            auto &transform = view.get<Transform>(entity);
            gameContext._runtime->drawText(text.font_id, text.text, transform.position,
                                           text.fontSize, text.color, text.centered);
        }

        auto viewButton = registry.view<Button, Transform>();
        for (auto entity : viewButton)
        {
            auto &button = viewButton.get<Button>(entity);
            auto &transform = viewButton.get<Transform>(entity);

            mlg::vec4 rect = {transform.position.x, transform.position.y, button.size.x,
                              button.size.y};
            if (button.selected) gameContext._runtime->drawRectangle(rect, false, button.color);
            gameContext._runtime->drawText(
                button.font_id, button.text + button.content,
                mlg::vec3(transform.position.x + 5, transform.position.y + 5, 0), button.fontSize,
                button.color, false);
            if (button.input && button.virtualKeyboard)
            {
                gameContext._runtime->drawSprite(keyboardSprite_id,
                                                 mlg::vec3(1920 / 2 - 450, 1080 - 350, 0));
                mlg::vec4 rect = {750 + 31 * selectedKey.x, 755 + 43 * selectedKey.y, 30, 30};
                gameContext._runtime->drawRectangle(rect, false, {255, 255, 255});
            }
        }
    }

    void moveSelection(mobs::Registry &registry, GameContext &gameContext, Button *selectedButton,
                       Transform *selectedTransform,
                       std::vector<std::pair<Button &, Transform &>> buttons)
    {
        selectedButton->selected = false;

        mlg::vec3 direction;
        if (gameContext._runtime->getKeyDown(KeyCode::UpArrow))
            direction = {0, -1, 0};
        else if (gameContext._runtime->getKeyDown(KeyCode::DownArrow))
            direction = {0, 1, 0};
        else if (gameContext._runtime->getKeyDown(KeyCode::LeftArrow))
            direction = {-1, 0, 0};
        else if (gameContext._runtime->getKeyDown(KeyCode::RightArrow))
            direction = {1, 0, 0};
        else
        {
            selectedButton->selected = true;
            return;
        }

        Button *newSelectedButton = nullptr;
        float minAdjustedDistance = std::numeric_limits<float>::max();
        float penaltyFactor = 2.0f;  // Adjust this factor to control how much the perpendicular
                                     // distance affects the priority.

        for (auto &[button, transform] : buttons)
        {
            if (&button == selectedButton) continue;

            mlg::vec3 toButton = transform.position - selectedTransform->position;
            float directionalDistance = toButton.dot(direction);
            float perpendicularDistance = (toButton - direction * directionalDistance).length();

            // Compute the adjusted distance with a penalty for the perpendicular distance.
            float adjustedDistance = directionalDistance + penaltyFactor * perpendicularDistance;

            if (directionalDistance > 0 && adjustedDistance < minAdjustedDistance)
            {
                minAdjustedDistance = adjustedDistance;
                newSelectedButton = &button;
            }
        }

        if (newSelectedButton)
            newSelectedButton->selected = true;
        else
            selectedButton->selected = true;
    }

    void buttonAction(mobs::Registry &registry, GameContext &gameContext, Button &button)
    {
        try
        {
            gameContext.get<CppScriptComponent>(button.entity)
                .onButtonPressedAll(registry, gameContext, button.action);
        }
        catch (const std::exception &e)
        {
            std::cerr << "no action binded to button" << std::endl;
        }
    }

   private:
    std::string keys = "0123456789   abcdefghijklmnopqrstuvwxyz.            ";

    mlg::vec3 selectedKey = {0, 0, 0};
    int keyboardSprite_id;
    // Member variables
};

}  // namespace RType

#endif  // DRAWABLESYSTEM_H