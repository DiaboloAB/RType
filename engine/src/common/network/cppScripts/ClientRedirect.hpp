/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef CLIENTREDIRECT_HPP
#define CLIENTREDIRECT_HPP

#include <iostream>

#include "common/ICppScript.hpp"
#include "gameContext/GameContext.hpp"

namespace RType
{

class ClientRedirect : public RType::ICppScript
{
   public:
    void start(mobs::Registry &registry, GameContext &gameContext) override
    {
        this->_redirecter[std::type_index(typeid(dimension::HiClient))] = []()
        { std::cerr << "Bonjour le 2" << std::endl; };
        this->_redirecter[std::type_index(typeid(dimension::Ping))] = []()
        { std::cerr << "Bonjour le 3" << std::endl; };
        this->_redirecter[std::type_index(typeid(dimension::UpdateEntity))] = []()
        { std::cerr << "Bonjour le 4" << std::endl; };
        this->_redirecter[std::type_index(typeid(dimension::CreateEntity))] = []()
        { std::cerr << "Bonjour le 5" << std::endl; };
        this->_redirecter[std::type_index(typeid(dimension::DestroyEntity))] = []()
        { std::cerr << "Bonjour le 6" << std::endl; };
        this->_redirecter[std::type_index(typeid(dimension::MoveEntity))] = []()
        { std::cerr << "Bonjour le 7" << std::endl; };
    }

    void update(mobs::Registry &registry, GameContext &gameContext) override
    {
        try
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
                auto typeIndex = networkC.factory.getIndexFromType(packet.first->getPacketType());
                if (this->_redirecter.find(typeIndex) != this->_redirecter.end())
                    this->_redirecter.at(typeIndex)();
                _rcvQueue.pop();
                networkC.client->popReceiveQueue();
            }
        }
        catch (std::exception &e)
        {
            ERR_LOG("ClientRedirect", std::string("Something went wrong {") + e.what() + "}");
        }
    }
    static constexpr const char *name = "ClientRedirect";

   private:
    std::map<std::type_index, std::function<void()>> _redirecter;
};

}  // namespace RType

#endif  // CLIENTREDIRECT_HPP