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
            /**
             * @brief Construct HiClientPacket object that will be send to client.
             * 
             * @param entityId : Id of the entity that will be created.
             * @return HiClientPacket object.
             */
            HiClientPacket(uint32_t entityId);
            
            /**
             * @brief Construct new HiClientPacket object with serialized data by deserializing them.
             * 
             * @param buffer: Serialized packet data to deserialize.
             * @return HiClientPacket object.
             */
            HiClientPacket(std::vector<char> &buffer);

            /**
             * @brief Destruct HiClientPacket object.
             */
            ~HiClientPacket();
        public:
            /**
             * @brief Serialize class data to binary to make it sendable by NetworkHandler.
             * 
             * @return std::vector<char> that represent serialization of entityId to binary.
             */
            std::vector<char> serializeData() const override;
        private:
            uint32_t _entityId;
    };
}