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
    void update(mobs::Registry &registry, GameContext &gameContext) override {}

    void onButtonPressed(mobs::Registry &registry, GameContext &gameContext,
                         std::string action, ...) override
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
        }
        else if (action == "startGame")
        {
            gameContext._sceneManager.switchScene("scene2");
        }
    }

    static constexpr const char *name = "Menu";

   private:
    bool fullscreen = false;
    int _eventID = 0;
};

}  // namespace RType

#endif  // MENU_HPP