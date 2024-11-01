/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef ROOMREDIRECT_HPP
#define ROOMREDIRECT_HPP

#include <iostream>

#include "common/ICppScript.hpp"
#include "common/network/cppScripts/redirect/ConnectionRedirect.hpp"
#include "common/network/cppScripts/redirect/EventRedirect.hpp"
#include "gameContext/GameContext.hpp"
#include "utils/Timer.hpp"

namespace RType
{

class RoomRedirect : public RType::ICppScript
{
   public:
    void start(mobs::Registry &registry, GameContext &gameContext) override
    {
        this->_redirecter[std::type_index(typeid(dimension::Ping))] = 
        [](mobs::Registry &registry, GameContext &gameContext, PacketDatas &packet)
        { Network::ConnectionRedirect::handlePingRoom(registry, gameContext, packet); };
        this->_redirecter[std::type_index(typeid(dimension::ClientEvent))] = 
        [](mobs::Registry &registry, GameContext &gameContext, PacketDatas &packet)
        { Network::EventRedirect::handleEvent(registry, gameContext, packet); };
        
        this->timer.start();
    }

    void update(mobs::Registry &registry, GameContext &gameContext) override
    {
        try
        {
            auto &networkC = registry.get<NetworkRoom>(getEntity());
            auto _rcvQueue = networkC.room->getRcvQueue();

            timer.update(gameContext._deltaT);
            if (timer.getTime() > 0.5)
            {
                networkC.room->sendPing();
                timer.reset();
            }
            while (!_rcvQueue.empty())
            {
                auto packet = _rcvQueue.front();
                auto typeIndex = networkC.factory.getIndexFromType(packet.first->getPacketType());
                if (this->_redirecter.find(typeIndex) != this->_redirecter.end())
                    this->_redirecter.at(typeIndex)(registry, gameContext, packet);
                if (typeIndex != std::type_index(typeid(dimension::Ping)))
                {
                    auto validation =
                        networkC.factory.createEmptyPacket<dimension::PacketValidation>();
                    validation->setPacketReceiveTimeStamp(packet.first->getPacketTimeStamp());
                    validation->setPacketReceiveType(packet.first->getPacketType());
                    networkC.room->send(validation, packet.second, false);
                }
                _rcvQueue.pop();
                networkC.room->popReceiveQueue();
            }
        }
        catch (std::exception &e)
        {
            ERR_LOG("ClientRedirect", std::string("Something went wrong {") + e.what() + "}");
        }
    }
    static constexpr const char *name = "RoomRedirect";

   private:
    Timer timer;
    using PacketDatas = std::pair<std::shared_ptr<dimension::APacket>, asio::ip::udp::endpoint>;
    std::map<std::type_index, std::function<void(mobs::Registry &, GameContext &, PacketDatas &)>> _redirecter;
};

}  // namespace RType

#endif  // ROOMREDIRECT_HPP