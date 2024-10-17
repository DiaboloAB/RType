/**********************************************************************************
 *  Project: Dimension Network
 *  Description: Networking Game Library
 *  Author: Morgan LARGEOT, Maxence LARGEOT
 *  Create Time: 2024-10-17
 *  Location: Rennes
 **********************************************************************************/

#pragma once

#include <chrono>
#include <cstdint>
#include <cstring>
#include <exception>
#include <string>
#include <vector>

namespace dimension
{

/**
 * @class APacket
 * @brief Abstract used to create packet, serialize them and deserialize. The content of this class
 * to all packet including packet header and its serialization.
 */
class APacket
{
   public:
    /**
     * @brief Construct new APacket object with his type as param.
     *
     * @param type: Type of the packet (CREATEENTITY, NONE, ...)
     * @return APacket object.
     */
    APacket(uint8_t type);

    /**
     * @brief Construct new APacket object with serialized data by deserializing them.
     *
     * @param buffer: Serialized packet data to deserialize.
     * @return APacket object.
     */
    APacket(std::vector<char> &buffer);

    /**
     * @brief Define destructor to the default destructor of the class that implements APacket.
     */
    virtual ~APacket() = default;

    /**
     * @brief Get the total size of the packet using serialized data if it is possible.
     *
     * @param buffer: Serialized packet to get the size from.
     * @return Total size of the packet or throw an error.
     */
    static uint32_t getPacketSizeFromBuffer(std::vector<char> &buffer);

    /**
     * @brief Get the type of the packet using serialized data if it is possible.
     *
     * @param buffer: Serialized packet to get the type from.
     * @return Type of the packet or throw an error.
     */
    static uint8_t getPacketTypeFromBuffer(std::vector<char> &buffer);

   public:
    /**
     * @brief Call serialization of the header and data serialization to return
     * complete serialize packet.
     *
     * @return Binary serialized packet.
     */
    std::vector<char> serialize() const;

    /**
     * @brief Serialize packet header data (data from APacket).
     *
     * @return Binary serialized header.
     */
    std::vector<char> serializeHeader() const;

    /**
     * @brief Serialize packet data (data from class that inherits APacket).
     *
     * @return Binary serialized data.
     */
    virtual std::vector<char> serializeData() const = 0;

   public:
    uint32_t getPacketSize() const;
    uint8_t getPacketType() const;
    uint64_t getPacketTimeStamp() const;
    uint32_t getHeaderSize() const;

   protected:
    uint32_t _packetSize;
    uint8_t _packetType;
    uint64_t _packetTimeStamp;
    uint16_t _packetDataSize;

   public:
    class PacketException : public std::exception
    {
       public:
        PacketException(std::string msg) : _msg(msg){};
        ~PacketException(){};

       private:
        const char *what() const noexcept override { return _msg.c_str(); };

       private:
        std::string _msg;
    };
};
}  // namespace dimension