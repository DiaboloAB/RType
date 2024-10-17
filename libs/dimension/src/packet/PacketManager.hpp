/**********************************************************************************
 *  Project: Dimension Network
 *  Description: Networking Game Library
 *  Author: Morgan LARGEOT, Maxence LARGEOT
 *  Create Time: 2024-10-17
 *  Location: Rennes
  **********************************************************************************/

#pragma once

#include <memory>
#include <functional>
#include <unordered_map>
#include <typeindex>
#include <packet/APacket.hpp>

namespace dimension {
    class PacketManager {
        public:
            PacketManager();
            ~PacketManager();
        public:
            template<typename Packet>
            void registerPacketToSend() {
                static_assert(std::is_base_of<APacket, Packet>::value, "Registration Error : Packet must derive from APacket !");
                this->_packetToSendFactory[std::type_index(typeid(Packet))] = []() {return std::make_shared<Packet>();};
            };

            template<typename Packet>
            std::shared_ptr<Packet> createPacketToSend() {
                const std::type_index typeIndex(typeid(Packet));
                if (this->_packetToSendFactory.find(typeIndex) == this->_packetToSendFactory.end())
                    throw PacketManagerError("PacketManagerError : Packet Type not registered !");
                return this->_packetToSendFactory[typeIndex]();
            };

            template<typename Packet>
            void registerPacketDeserialization(uint8_t packetType) {
                static_assert(std::is_base_of<APacket, Packet>::value, "Registration Error : Packet must derive from APacket !");
                this->_packetToDeserializeFactory[packetType] = [](std::vector<char> &buffer) {return std::make_shared<Packet>(buffer);};
            }

            std::shared_ptr<APacket> createPacketFromBuffer(std::vector<char> &buffer) {
                try {
                    uint8_t packetType = APacket::getPacketTypeFromBuffer(buffer);
                    if (this->_packetToDeserializeFactory.find(packetType) == this->_packetToDeserializeFactory.end())
                        throw PacketManagerError("PacketManagerError : Packet Type not registered to be deserialized !");
                    return this->_packetToDeserializeFactory[packetType](buffer);
                } catch (PacketManagerError &e) {
                    throw;
                } catch (std::exception &e) {
                    throw PacketManagerError(
                        std::string("PacketManagerError: Unable to deserialize packet :  {") + e.what() + std::string("}"));
                }
            };

        private:
            std::unordered_map<std::type_index, std::function<std::shared_ptr<APacket>()>> _packetToSendFactory;
            std::unordered_map<uint8_t, std::function<std::shared_ptr<APacket>(std::vector<char> &)>> _packetToDeserializeFactory;

        public:
            class PacketManagerError : public std::exception {
                public:
                    PacketManagerError(std::string error) : _error(error) {};
                    ~PacketManagerError() {};
                private:
                    const char *what() const noexcept override { return _error.c_str(); };
                private:
                    std::string _error;
            };
    };
}
