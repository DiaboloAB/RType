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

#include "GameInstance.hpp"

namespace RType::Network {
/**
 * @struct RoomState
 * 
 * @brief Stores all necessary informations to run a room into the server.
 */
struct RoomState
{
    unsigned int _port;
    int _nbConnected = 0;
    std::list<asio::ip::udp::endpoint> _endpoints;
    bool _inGame = false;
    std::shared_ptr<GameInstance> _gameInstance = nullptr;
    std::shared_ptr<std::thread> _roomThread = nullptr;
};
}