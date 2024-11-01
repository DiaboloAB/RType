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
#include "IdFactory.hpp"

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
    dimension::IdFactory idFactory;

    NetworkRoom() {}
    static constexpr const char* name = "NetworkRoom";
};

struct NetworkData
{
    uint32_t _id;
    std::string _authority;

    NetworkData() {}
    static constexpr const char* name = "NetworkData";
};
}  // namespace RType

#endif  // NETWORKCOMP_H