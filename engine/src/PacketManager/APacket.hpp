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

namespace RType::Network {

    enum PacketType : uint8_t {
        NONE = 0,
        CREATEENTITY = 1,
        DESTROYENTITY = 2,
        MOVEENTITY = 3,
        UPDATEENTITY = 4,
    };

    class APacket {
        public:
            APacket(PacketType type) {};
            virtual ~APacket() = 0;
        public:
            std::vector<char> serialize() const;
            std::vector<char> serializeHeader() const;
            virtual std::vector<char> serializeData() const = 0;
        protected:
            uint32_t _packetSize;
            PacketType _packetType;
            uint64_t _packetTimeStamp;
            uint16_t _packetDataSize;
    };
}