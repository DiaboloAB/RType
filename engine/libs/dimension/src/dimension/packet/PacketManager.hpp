/**********************************************************************************
 *  Project: Dimension Network
 *  Description: Networking Game Library
 *  Author: Morgan LARGEOT, Maxence LARGEOT
 *  Create Time: 2024-10-17
 *  Location: Rennes
 **********************************************************************************/

#pragma once

#include <APacket.hpp>
#include <functional>
#include <iostream>
#include <memory>
#include <typeindex>
#include <unordered_map>

#include "HiServer.hpp"

namespace dimension
{

/**
 * @class PacketManager
 *
 * @brief Manages the creation of packets derived from APacket, allowing both
 * empty packet creation and deserialization from serialized data.
 */
class PacketManager
{
   public:
    PacketManager();
    ~PacketManager();

   public:
    /**
     * @brief Registers a new packet type, derived from APacket, into the factory map.
     *
     * This allows the creation of an empty packet of the specified type at runtime,
     * enabling dynamic packet handling and instantiation based on the packet type.
     *
     * @tparam Packet The type of the packet to be registered.
     * @return uint8_t representing id of the packet type registered.
     */
    template <typename Packet>
    std::uint8_t registerPacket()
    {
        static_assert(std::is_base_of<APacket, Packet>::value,
                      "Registration Error : Packet must derive from APacket !");
        if (this->_typeId == 255)
            throw PacketManagerError("PacketManagerError: Maximum size of packet is registered.");
        std::type_index index(typeid(Packet));
        this->_packetToSendFactory[index] = [](uint8_t typeId)
        { return std::make_shared<Packet>(typeId); };
        this->_packetToDeserializeFactory[index] = [](std::vector<char> &buffer)
        { return std::make_shared<Packet>(buffer); };
        this->_idMap.emplace(this->_typeId, index);
        this->_typeId++;
        return this->_typeId - 1;
    };

    /**
     * @brief Creates an empty packet of the specified type to be sent.
     *
     * Utilizes the provided packet type to instantiate an empty packet object,
     * facilitating the preparation and dispatch of network data.
     *
     * @tparam Packet The type of the packet to be created.
     * @return std::shared_ptr<Packet> A shared pointer to the newly created packet.
     */
    template <typename Packet>
    std::shared_ptr<Packet> createPacketToSend()
    {
        const std::type_index typeIndex(typeid(Packet));
        for (auto &packetId : this->_idMap)
            if (packetId.second == typeIndex)
                return std::dynamic_pointer_cast<Packet>(
                    this->_packetToSendFactory[typeIndex](packetId.first));
        throw PacketManagerError("PacketManagerError : Packet Type not registered !");
    };

    /**
     * @brief Creates a Packet from serialized data contained in a buffer.
     *
     * Extracts the packet type from the buffer and uses it to invoke the appropriate
     * constructor, returning a deserialized packet.
     *
     * @param buffer The buffer containing the serialized packet data.
     * @return std::shared_ptr<APacket> A shared pointer to the deserialized packet.
     */
    std::shared_ptr<APacket> createPacketFromBuffer(std::vector<char> &buffer)
    {
        try
        {
            uint8_t packetType = APacket::getPacketTypeFromBuffer(buffer);
            std::type_index index = this->getIndexFromType(packetType);
            std::shared_ptr<APacket> packet = this->_packetToDeserializeFactory[index](buffer);
            if (packet->getPacketSize() > buffer.size())
                throw PacketManagerError(
                    "PacketManagerError : Incomplete deserialzation due to incomplete buffer !");
            return packet;
        }
        catch (PacketManagerError &e)
        {
            throw;
        }
        catch (std::exception &e)
        {
            throw PacketManagerError(
                std::string("PacketManagerError: Unable to deserialize packet :  {") + e.what() +
                std::string("}"));
        }
    };

   public:
    std::type_index getIndexFromType(uint8_t packetType) const
    {
        if (this->_idMap.find(packetType) == this->_idMap.end())
            throw PacketManagerError("PacketManagerError : Packet type not registered.");
        return this->_idMap.at(packetType);
    }

    uint8_t getTypeFromIndex(std::type_index packetIndex) const
    {
        for (auto &registered : this->_idMap)
            if (registered.second == packetIndex) return registered.first;
        throw PacketManagerError("PacketManagerError : Packet index not registered.");
    }

   private:
    std::unordered_map<std::type_index, std::function<std::shared_ptr<APacket>(uint8_t type)>>
        _packetToSendFactory;
    std::unordered_map<std::type_index,
                       std::function<std::shared_ptr<APacket>(std::vector<char> &)>>
        _packetToDeserializeFactory;
    std::unordered_map<std::uint8_t, std::type_index> _idMap;
    uint8_t _typeId = 0;

   public:
    class PacketManagerError : public std::exception
    {
       public:
        PacketManagerError(std::string error) : _error(error){};
        ~PacketManagerError(){};

       private:
        const char *what() const noexcept override { return _error.c_str(); };

       private:
        std::string _error;
    };
};
}  // namespace dimension
