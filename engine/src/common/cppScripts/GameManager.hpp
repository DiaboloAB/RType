/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "common/ICppScript.hpp"
#include "common/components.hpp"
#include "gameContext/GameContext.hpp"

namespace RType
{

class GameManager : public RType::ICppScript
{
   public:
    GameManager() {}
    ~GameManager() {}

    void start(mobs::Registry &registry, GameContext &gameContext) override
    {
        try
        {
            Audio &audio = registry.get<Audio>(_entity);
            audio.audioQueue.push("assets/sounds/menu.ogg");
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    void update(mobs::Registry &registry, GameContext &gameContext) override {}

    void callFunction(const std::string &functionName, mobs::Registry &registry,
                      GameContext &gameContext) override
    {
        if (functionName == "Credit")
        {
            gameContext._sceneManager._nextScene = "credits.json";
        }
        if (functionName == "Solo")
        {
            gameContext._sceneManager._nextScene = "scenes2.json";
        }
        if (functionName == "Multi")
        {
            gameContext._sceneManager._nextScene = "scenes1.json";
        }
    }

    void setEntity(mobs::Entity entity) override { _entity = entity; }

   private:
    mobs::Entity _entity;
};

}  // namespace RType

#endif  // GAMEMANAGER_H