/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#pragma once

#include <list>
#include <memory>
#include <asio.hpp>
#include <thread>

namespace RType::Network {
struct RoomState
{
    unsigned int _port;
    int _nbConnected = 0;
    std::list<asio::ip::udp::endpoint> _endpoints;
    bool _inGame = false;
    std::shared_ptr<std::thread> _roomThread = nullptr;
};
}