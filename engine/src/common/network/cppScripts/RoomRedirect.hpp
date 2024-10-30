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
#include "gameContext/GameContext.hpp"

namespace RType
{

class RoomRedirect : public RType::ICppScript
{
   public:
    void start(mobs::Registry &registry, GameContext &gameContext) override
    {
        this->_redirecter[std::type_index(typeid(dimension::Ping))] = []()
        { std::cerr << "Bonjour le 3" << std::endl; };
        this->_redirecter[std::type_index(typeid(dimension::ClientEvent))] = []()
        { std::cerr << "Bonjour le 4" << std::endl; };
    }

    void update(mobs::Registry &registry, GameContext &gameContext) override
    {
        try
        {
            auto &networkC = registry.get<NetworkRoom>(getEntity());
            auto _rcvQueue = networkC.room->getRcvQueue();
            while (!_rcvQueue.empty())
            {
                auto packet = _rcvQueue.front();
                auto validation = networkC.factory.createEmptyPacket<dimension::PacketValidation>();
                validation->setPacketReceiveTimeStamp(packet.first->getPacketTimeStamp());
                validation->setPacketReceiveType(packet.first->getPacketType());
                networkC.room->send(validation, packet.second, false);
                auto typeIndex = networkC.factory.getIndexFromType(packet.first->getPacketType());
                if (this->_redirecter.find(typeIndex) != this->_redirecter.end())
                    this->_redirecter.at(typeIndex)();
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
    std::map<std::type_index, std::function<void()>> _redirecter;
};

}  // namespace RType

#endif  // ROOMREDIRECT_HPP