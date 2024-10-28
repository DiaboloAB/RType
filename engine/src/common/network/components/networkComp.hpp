/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef NETWORKCOMP_H
#define NETWORKCOMP_H

#include "Client.hpp"
#include "Room.hpp"

// std
#include <memory>

namespace RType
{
struct NetworkClient
{
    std::shared_ptr<dimension::Client> client = nullptr;
    dimension::PacketFactory factory;

    NetworkClient()
    {
        client = std::make_shared<dimension::Client>(std::make_shared<dimension::PacketFactory>());
    }
    static constexpr const char* name = "NetworkClient";
};

struct NetworkRoom
{
    std::shared_ptr<dimension::Room> room = nullptr;
    dimension::PacketFactory factory;

    NetworkRoom(std::string host, unsigned int port, std::string code)
    {
        room = std::make_shared<dimension::Room>(std::make_shared<dimension::PacketFactory>(), host,
                                                 port, code);
    }
};
}  // namespace RType

#endif  // NETWORKCOMP_H