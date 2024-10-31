/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef COMSERVER_HPP
#define COMSERVER_HPP

#include <iostream>

#include "ClientEventType.hpp"
#include "common/ICppScript.hpp"
#include "gameContext/GameContext.hpp"

namespace RType
{

class ComServer : public RType::ICppScript
{
   public:
    void update(mobs::Registry &registry, GameContext &gameContext) override
    {
        auto &networkC = registry.get<NetworkClient>(getEntity());
        if (gameContext._runtime->getKeyDown(KeyCode::Enter))
        {
            networkC.client->connectServer("127.0.0.1", 8581);
        }
        if (gameContext._runtime->getKeyDown(KeyCode::R))
        {
            auto event = networkC.factory.createEmptyPacket<dimension::ClientEvent>();
            event->setClientEvent(dimension::ClientEventType::ROOM);
            event->setDescription("join=rd");
            if (networkC.client->_serverEndpoint)
                networkC.client->send(event, *networkC.client->_serverEndpoint);
        }
        if (gameContext._runtime->getKeyDown(KeyCode::L))
        {
            auto event = networkC.factory.createEmptyPacket<dimension::ClientEvent>();
            event->setClientEvent(dimension::ClientEventType::ROOM);
            event->setDescription("end=N");
            if (networkC.client->_serverEndpoint)
                networkC.client->send(event, *networkC.client->_serverEndpoint);
        }
        if (gameContext._runtime->getKeyDown(KeyCode::S))
        {
            auto event = networkC.factory.createEmptyPacket<dimension::ClientEvent>();
            event->setClientEvent(dimension::ClientEventType::ROOM);
            event->setDescription("start=N");
            if (networkC.client->_serverEndpoint)
                networkC.client->send(event, *networkC.client->_serverEndpoint);
        }
    }
    static constexpr const char *name = "ComServer";

   private:
};

}  // namespace RType

#endif  // COMSERVER_HPP