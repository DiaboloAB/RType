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
#include "common/network/cppScripts/redirect/UpdateRedirect.hpp"
#include "common/network/cppScripts/redirect/EntityRedirect.hpp"

namespace RType
{

class ClientRedirect : public RType::ICppScript
{
   public:
    void start(mobs::Registry &registry, GameContext &gameContext) override
    {
        //this->_redirecter[std::type_index(typeid(dimension::HiClient))] = []()
        //{ std::cerr << "Bonjour le 2" << std::endl; };
        //this->_redirecter[std::type_index(typeid(dimension::Ping))] = []()
        //{ std::cerr << "Bonjour le 3" << std::endl; };
        this->_redirecter[std::type_index(typeid(dimension::UpdateEntity))] = [](
            mobs::Registry &registry, GameContext &gameContext, PacketDatas &packet)
        { Network::UpdateRedirect::update(registry, gameContext, packet); };
        this->_redirecter[std::type_index(typeid(dimension::CreateEntity))] = [](
            mobs::Registry &registry, GameContext &gameContext, PacketDatas &packet)
        { Network::EntityRedirect::create(registry, gameContext, packet); };
        this->_redirecter[std::type_index(typeid(dimension::DestroyEntity))] = [](
            mobs::Registry &registry, GameContext &gameContext, PacketDatas &packet)
        { Network::EntityRedirect::destroy(registry, gameContext, packet); };
        this->_redirecter[std::type_index(typeid(dimension::MoveEntity))] = [](
            mobs::Registry &registry, GameContext &gameContext, PacketDatas &packet)
        { Network::EntityRedirect::move(registry, gameContext, packet); };
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
                    this->_redirecter.at(typeIndex)(registry, gameContext, packet);
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
    using PacketDatas = std::pair<std::shared_ptr<dimension::APacket>, asio::ip::udp::endpoint>;
    std::map<std::type_index, std::function<void(mobs::Registry &, GameContext &, PacketDatas &)>> _redirecter;
};

}  // namespace RType

#endif  // CLIENTREDIRECT_HPP