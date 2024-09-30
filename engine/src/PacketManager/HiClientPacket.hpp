/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#pragma once

    #include "APacket.hpp"

namespace RType::Network {
    class HiClientPacket : public APacket {
        public:
            HiClientPacket(uint32_t entityId);
            HiClientPacket(std::vector<char> &buffer);
            ~HiClientPacket();
        public:
            std::vector<char> serializeData() const override;
        private:
            uint32_t _entityId;
    };
}