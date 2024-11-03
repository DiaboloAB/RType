/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include "common/ICppScript.hpp"
#include "common/cppScripts/Terrain.hpp"
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
                if (event.type == "instantiate")
                {
                    mobs::Entity entity =
                        gameContext._sceneManager.instantiate(event.prefab, gameContext);
                    auto &transform = registry.get<Transform>(entity);
                    auto &basic = registry.get<Basics>(entity);
                    auto &networkData = registry.get<NetworkData>(entity);

                    basic.tag = event.prefab + std::to_string(_eventID);
                    transform.position = event.position;
                    transform.scale *= event.scale;
                    _eventID++;

                    NetworkRoom &room = registry.get<NetworkRoom>(registry.view<NetworkRoom>().front());
                    uint32_t networkId = room.idFactory.generateNetworkId();
                    networkData._id = networkId;
                    sendEventSpawn(registry, event.prefab, event.position, event.scale, networkId, room);
                }
                if (event.type == "stopScrolling")
                {
                    mobs::Registry::View view = registry.view<Basics, CppScriptComponent>();
                    for (auto _entity : view)
                    {
                        auto &cppScript = view.get<CppScriptComponent>(_entity);
                        if (cppScript.getScript<Terrain>() != nullptr)
                        {
                            cppScript.getScript<Terrain>()->setScrolling(false);
                        }
                    }
                }
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
                event++;
            }
        }
    }

    static constexpr const char *name = "GameManager";

   private:
    int _eventID = 0;


    void sendEventSpawn(mobs::Registry &registry, std::string prefab, mlg::vec3 position, mlg::vec3 scale, uint32_t networkId, NetworkRoom &room)
    {
        auto spawnServe = room.factory.createEmptyPacket<dimension::CreateEntity>();

        spawnServe->setNetworkId(networkId);

        spawnServe->setEntityToCreate(prefab);
        spawnServe->setPosX(position.x);
        spawnServe->setPosY(position.y);
        spawnServe->setScaleX(scale.x);
        spawnServe->setScaleY(scale.y);

        room.room->sendToAll(spawnServe);
    }
};

}  // namespace RType

#endif  // GAMEMANAGER_HPP