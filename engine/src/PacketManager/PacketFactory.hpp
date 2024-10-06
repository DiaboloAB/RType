/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#pragma once

#include <exception>
#include <functional>
#include <memory>
#include <unordered_map>

#include "APacket.hpp"
#include "AdiosServerPacket.hpp"
#include "ClientEventPacket.hpp"
#include "CreateEntityPacket.hpp"
#include "DestroyEntityPacket.hpp"
#include "HiClientPacket.hpp"
#include "HiServerPacket.hpp"
#include "KickClientPacket.hpp"
#include "MoveEntityPacket.hpp"
#include "PacketValidationPacket.hpp"
#include "PingPacket.hpp"
#include "UpdateEntityPacket.hpp"

namespace RType::Network
{

/**
 * @class PacketFactory
 *
 * @brief This class is a design pattern use to create all types of packets. These packets
 * are used for network communication between client and server.
 */
class PacketFactory
{
   public:
    /**
     * @brief Create PacketFactory object that will create packets.
     *
     * @return PacketFactory object.
     */
    PacketFactory();

    /**
     * @brief Copy constructor of PacketFactory object use to copy PacketFactory data into another.
     *
     * @return PacketFactory object.
     */
    PacketFactory(const PacketFactory &obj);

    /**
     * @brief Destroy PacketFactory object.
     */
    ~PacketFactory();

   public:
    std::unordered_map<PacketType, std::function<std::shared_ptr<APacket>(std::vector<char> &)>>
    getCreationMap() const;

   public:
    /**
     * @brief Create a new packet with the buffer passed as parameter.
     *
     * @param buffer : Serialized data used to create a packet.
     * @return Pointer in a deserialized packet or throw an error if invalid packet.
     */
    std::shared_ptr<APacket> createPacketFromBuffer(std::vector<char> &buffer);

   public:
    class PacketFactoryError : public std::exception
    {
       public:
        PacketFactoryError(std::string msg) : _msg(msg){};
        ~PacketFactoryError(){};

       private:
        const char *what() const noexcept override { return _msg.c_str(); };

       private:
        std::string _msg;
    };

   private:
    std::unordered_map<PacketType, std::function<std::shared_ptr<APacket>(std::vector<char> &)>>
        _creationMap;
};
}  // namespace RType::Network
