/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "common/ICppScript.hpp"
#include "common/cppScripts/Terrain.hpp"
#include "gameContext/GameContext.hpp"

namespace RType
{

class GameState : public RType::ICppScript
{
   public:
    void update(mobs::Registry &registry, GameContext &gameContext) override
    {
        bool isPlayerAlive = false;
        bool isAllyAlive = false;
        auto view = registry.view<Basics, CppScriptComponent>();
        for (auto entity : view)
        {
            if (view.get<Basics>(entity).tag == "player")
            {
                isPlayerAlive = true;
                break;
            }
            if (view.get<Basics>(entity).tag == "ally")
            {
                isAllyAlive = true;
                break;
            }
        }
        if (!isPlayerAlive && !isAllyAlive)
        {
            try {
                auto &networkC = gameContext.get<NetworkClient>("NetworkCom");

                if (networkC.client->_serverEndpoint) {
                    gameContext._sceneManager.switchScene("gameOver");
                    return;
                }
            } catch (const std::exception &e) {}
            exit(0);
        }
    }

    static constexpr const char *name = "GameState";

   private:
};

}  // namespace RType

#endif  // GAMESTATE_HPP