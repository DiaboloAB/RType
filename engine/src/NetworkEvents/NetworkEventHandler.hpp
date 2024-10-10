/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#pragma once

#include <unordered_map>
#include <functional>
#include <NetworkPacketManager/ClientEventPacket.hpp>
#include <NetworkHandler/NetworkIdHandler.hpp>
#include <mobs/mobs.hpp>


namespace RType::Network {
class NetworkEventHandler {
    public:
        NetworkEventHandler();
        ~NetworkEventHandler();
    private:
        std::unordered_map<ClientEvent, std::function<void()>> 
            _eventMap;
        NetworkIdHandler _idHandler;
};
}