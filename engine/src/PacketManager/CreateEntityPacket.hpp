/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#pragma once

    #include "APacket.hpp"

namespace RType::Network {
    class CreateEntityPacket : public APacket {
        public:
            CreateEntityPacket(uint32_t entityId, float posX, float posY);
            ~CreateEntityPacket() override;
        public:
            std::vector<char> serializeData() const override;
        private:
            uint32_t _entityId;
            float _posX;
            float _posY;
    };
}
