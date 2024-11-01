/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include "common/ICppScript.hpp"
#include "gameContext/GameContext.hpp"

namespace RType
{

class GameManager : public RType::ICppScript
{
   public:

    void update(mobs::Registry &registry, GameContext &gameContext) override
    {
        auto &eventManager = registry.get<EventManager>(getEntity());

        for (auto &event : eventManager.eventList)
        {
            event.delay -= gameContext._deltaT;
            if (event.delay <= 0)
            {
                mobs::Entity entity =
                    gameContext._sceneManager.instantiate(event.prefab, gameContext);
                auto &transform = registry.get<Transform>(entity);
                auto &basic = registry.get<Basics>(entity);

                basic.tag = event.prefab + std::to_string(_eventID);
                transform.position = event.position;
                _eventID++;
            }
        }
        for (auto event = eventManager.eventList.begin(); event != eventManager.eventList.end();)
        {
            if (event->delay <= 0)
            {
                event = eventManager.eventList.erase(event);
            }
            else
            {
                ++event;
            }
        }
    }

    static constexpr const char *name = "GameManager";

   private:
    int _eventID = 0;
};

}  // namespace RType

#endif  // GAMEMANAGER_HPP