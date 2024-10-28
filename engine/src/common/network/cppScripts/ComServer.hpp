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
            auto &networkC = registry.get<NetworkClient>(getEntity());
            auto event = networkC.factory.createEmptyPacket<dimension::ClientEvent>();
            event->setClientEvent(dimension::ClientEventType::ROOM);
            event->setDescription("cr=pv");
            if (networkC.client->_serverEndpoint)
                networkC.client->send(event, *networkC.client->_serverEndpoint);
        }
    }

   private:
};

}  // namespace RType

#endif  // COMSERVER_HPP