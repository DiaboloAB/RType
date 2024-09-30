/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#pragma once

    #include "APacket.hpp"

namespace RType::Network {
    class HiServerPacket : public APacket {
        public:
            /**
             * @brief Construct HiServerPacket object that will be send to client.
             * 
             * @param entityId : Id of the entity that will be created.
             * @return HiServerPacket object.
             */
            HiServerPacket(float runtimeVersion);
            
            /**
             * @brief Construct new HiServerPacket object with serialized data by deserializing them.
             * 
             * @param buffer: Serialized packet data to deserialize.
             * @return HiServerPacket object.
             */
            HiServerPacket(std::vector<char> &buffer);

            /**
             * @brief Destruct HiServerPacket object.
             */
            ~HiServerPacket();
        public:
            /**
             * @brief Serialize class data to binary to make it sendable by NetworkHandler.
             * 
             * @return std::vector<char> that represent serialization of entityId to binary.
             */
            std::vector<char> serializeData() const override;
        private:
            float _runtimeVersion;
    };
}