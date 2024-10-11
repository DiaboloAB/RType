/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include <NetworkEvents/NetworkEventHandler.hpp>

namespace RType::Network {
    
    NetworkEventHandler::NetworkEventHandler(NetworkIdHandler &idHandler) : _idHandler(idHandler) {
        this->_eventMap[GAME_START] = [this](asio::ip::udp::endpoint &sender, mobs::Registry &registry, GameContext &gameContext, NetworkIdHandler &idHandler)
            {return GameStartEvent::update(sender, registry, gameContext, idHandler);};
    }

    NetworkEventHandler::~NetworkEventHandler() {}

    void NetworkEventHandler::update(ClientEvent event, asio::ip::udp::endpoint &sender, mobs::Registry &registry, GameContext &gameContext)
    {
        auto targetEvent = this->_eventMap.find(event);
        if (targetEvent == this->_eventMap.end())
            return;
        this->_eventMap[event](sender, registry, gameContext, this->_idHandler);
    }
}

