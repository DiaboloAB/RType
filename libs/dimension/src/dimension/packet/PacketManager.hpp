/**********************************************************************************
 *  Project: Dimension Network
 *  Description: Networking Game Library
 *  Author: Morgan LARGEOT, Maxence LARGEOT
 *  Create Time: 2024-10-17
 *  Location: Rennes
 **********************************************************************************/

#pragma once

#include <functional>
#include <memory>
#include <APacket.hpp>
#include <typeindex>
#include <unordered_map>
#include <iostream>

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
     */
    template <typename Packet>
    void registerPacketToSend()
    {
        static_assert(std::is_base_of<APacket, Packet>::value,
                      "Registration Error : Packet must derive from APacket !");
        this->_packetToSendFactory[std::type_index(typeid(Packet))] = []()
        { return std::make_shared<Packet>(); };
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
        if (this->_packetToSendFactory.find(typeIndex) == this->_packetToSendFactory.end())
            throw PacketManagerError("PacketManagerError : Packet Type not registered !");
        return this->_packetToSendFactory[typeIndex]();
    };

    /**
     * @brief Registers a packet type for deserialization.
     *
     * Links a packet type identifier with its constructor to deserialize a vector of chars
     * into the appropriate packet.
     *
     * @tparam Packet The packet class derived from APacket.
     * @param packetType Identifier for the packet type.
     */
    template <typename Packet>
    void registerPacketDeserialization(uint8_t packetType)
    {
        static_assert(std::is_base_of<APacket, Packet>::value,
                      "Registration Error : Packet must derive from APacket !");
        this->_packetToDeserializeFactory[packetType] = [](std::vector<char> &buffer)
        { return std::make_shared<Packet>(buffer); };
    }

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
            if (this->_packetToDeserializeFactory.find(packetType) ==
                this->_packetToDeserializeFactory.end())
                throw PacketManagerError(
                    "PacketManagerError : Packet Type not registered to be deserialized !");
            std::shared_ptr<APacket> packet = this->_packetToDeserializeFactory[packetType](buffer);
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

   private:
    std::unordered_map<std::type_index, std::function<std::shared_ptr<APacket>()>>
        _packetToSendFactory;
    std::unordered_map<uint8_t, std::function<std::shared_ptr<APacket>(std::vector<char> &)>>
        _packetToDeserializeFactory;

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
