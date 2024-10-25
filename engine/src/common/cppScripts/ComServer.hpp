/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef COMSERVER_HPP
#define COMSERVER_HPP

#include "common/ICppScript.hpp"
#include "gameContext/GameContext.hpp"
#include "ClientEventType.hpp"
#include <iostream>

namespace RType
{

class ComServer : public RType::ICppScript
{
   public:
    void update(mobs::Registry &registry, GameContext &gameContext) override
    {
        if (gameContext._runtime->getKey(KeyCode::Mouse0))
            std::cerr << "je trigger input" << std::endl;
        if (gameContext._runtime->getKeyDown(KeyCode::Enter)) {
            std::cerr << "je trigger key enter" << std::endl;
            auto &networkC = registry.get<NetworkClient>(_entity);
            networkC.client->connectServer("127.0.0.1", 8581);
        }
        if (gameContext._runtime->getKeyDown(KeyCode::R)) {
            auto &networkC = registry.get<NetworkClient>(_entity);
            auto event = networkC.factory.createEmptyPacket<dimension::ClientEvent>();
            event->setClientEvent(dimension::ClientEventType::ROOM);
            event->setDescription("cr");
            if (networkC.client->_serverEndpoint)
                networkC.client->send(event, *networkC.client->_serverEndpoint);
        }
    }
    void setEntity(mobs::Entity entity) override { _entity = entity; }

   private:
    mobs::Entity _entity;
};

}  // namespace RType

#endif  // COMSERVER_HPP