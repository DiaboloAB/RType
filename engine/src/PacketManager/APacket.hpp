/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#pragma once

    #include <vector>
    #include <cstdint>
    #include <cstring>
    #include <chrono>
    #include <exception>
    #include <string>

namespace RType::Network {

    /**
     * @brief All possible types of a packet.
     */
    enum PacketType : uint8_t {
        NONE = 0,
        HISERVER = 1,
        HICLIENT = 2,
        CREATEENTITY = 5,
    };

    /**
     * @class APacket
     * @brief Abstract used to create packet, serialize them and deserialize. The content of this class
     * to all packet including packet header and its serialization.
     */
    class APacket {
        public:

            /**
             * @brief Construct new APacket object with his type as param.
             * 
             * @param type: Type of the packet (CREATEENTITY, NONE, ...)
             * @return APacket object.
             */
            APacket(PacketType type);

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
        public:
            uint32_t getPacketSize() const;
            PacketType getPacketType() const;
            uint32_t getHeaderSize() const;

            /**
             * @brief Get the total size of the packet using serialized data if it is possible.
             * 
             * @param buffer: Serialized packet to get the size from.
             * @return Total size of the packet or throw an error.
             */
            uint32_t getPacketSizeFromBuffer(std::vector<char> &buffer) const;

            /**
             * @brief Get the type of the packet using serialized data if it is possible.
             * 
             * @param buffer: Serialized packet to get the type from.
             * @return Type of the packet or throw an error.
             */
            PacketType getPacketTypeFromBuffer(std::vector<char> &buffer) const; 
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
            class PacketException : public std::exception {
                public:
                    PacketException(std::string msg) : _msg(msg) {};
                    ~PacketException() {};
                private:
                    const char *what() const noexcept override {return _msg.c_str();};
                private:
                    std::string _msg;
            };
        protected:
            uint32_t _packetSize;
            PacketType _packetType;
            uint64_t _packetTimeStamp;
            uint16_t _packetDataSize;
    };
}