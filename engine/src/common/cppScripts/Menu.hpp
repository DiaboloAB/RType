/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef MENU_HPP
#define MENU_HPP

#include "common/ICppScript.hpp"
#include "gameContext/GameContext.hpp"

namespace RType
{

class Menu : public RType::ICppScript
{
   public:
    void load(mobs::Registry &registry, GameContext &gameContext) override
    {
        try {
            gameContext.get<Audio>("soundManager").audioQueue.push("sounds/mainTrack.ogg");
        } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }

    void update(mobs::Registry &registry, GameContext &gameContext) override
    {
        if (gameContext._sceneManager.getCurrentScene() != "menu" || gameContext._sceneManager.getCurrentScene() != "settings")
            return;
        if (gameContext._runtime->getKeyDown(KeyCode::UpArrow) || gameContext._runtime->getKeyDown(KeyCode::DownArrow) ||
            gameContext._runtime->getKeyDown(KeyCode::LeftArrow) || gameContext._runtime->getKeyDown(KeyCode::RightArrow)) {
            try {
                gameContext.get<Audio>("soundManager").audioQueue.push("sounds/bip.ogg");
            } catch (std::exception &e) {
                std::cerr << e.what() << std::endl;
            }
        }
    }

    void onButtonPressed(mobs::Registry &registry, GameContext &gameContext, std::string action) override
    {
        if (action == "settings")
            gameContext._sceneManager.switchScene("settings");
        else if (action == "exit")
            gameContext._running = false;
        else if (action == "return")
            gameContext._sceneManager.switchScene("menu");
        else if (action == "fullscreen")
        {
            fullscreen = !fullscreen;
            gameContext._runtime->FullScreenWindow();
            try {
                gameContext.get<Button>("fullscreen").text = fullscreen ? "Fullscreen: On" : "Fullscreen: Off";
            } catch (std::exception &e) {
                std::cerr << e.what() << std::endl;
            }
        }

    }

    static constexpr const char *name = "Menu";

   private:
    bool fullscreen = false;
    int _eventID = 0;
};

}  // namespace RType

#endif  // MENU_HPP