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
        auto &networkC = registry.get<NetworkClient>(_entity);
        auto _rcvQueue = networkC.client->getRcvQueue();
        while (!_rcvQueue.empty())
        {
            auto packet = _rcvQueue.front();
            auto validation = networkC.factory.createEmptyPacket<dimension::PacketValidation>();
            validation->setPacketReceiveTimeStamp(packet.first->getPacketTimeStamp());
            validation->setPacketReceiveType(packet.first->getPacketType());
            networkC.client->send(validation, packet.second, false);
            _rcvQueue.pop();
            networkC.client->popReceiveQueue();
        }
        if (gameContext._runtime->getKeyDown(KeyCode::Enter))
        {
            networkC.client->connectServer("127.0.0.1", 8581);
        }
        if (gameContext._runtime->getKeyDown(KeyCode::R))
        {
            auto &networkC = registry.get<NetworkClient>(_entity);
            auto event = networkC.factory.createEmptyPacket<dimension::ClientEvent>();
            event->setClientEvent(dimension::ClientEventType::ROOM);
            event->setDescription("join=rd");
            if (networkC.client->_serverEndpoint)
                networkC.client->send(event, *networkC.client->_serverEndpoint);
        }
        if (gameContext._runtime->getKeyDown(KeyCode::L))
        {
            auto &networkC = registry.get<NetworkClient>(_entity);
            auto event = networkC.factory.createEmptyPacket<dimension::ClientEvent>();
            event->setClientEvent(dimension::ClientEventType::ROOM);
            event->setDescription("leave=N");
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