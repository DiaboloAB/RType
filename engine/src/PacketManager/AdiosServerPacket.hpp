/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#pragma once

    #include "APacket.hpp"

namespace RType::Network {

    /**
     * @class AdiosServerPacket
     * 
     * @brief Class used to create a Packet that can be serialize and deserialize. This packet hold
     * main information used by client to inform server of logout.
     */
    class AdiosServerPacket : public APacket {
        public:
            /**
             * @brief Construct AdiosServerPacket object that will be send to sever.
             * 
             * @return AdiosServerPacket object.
             */
            AdiosServerPacket();
            
            /**
             * @brief Construct new AdiosServerPacket object with serialized data by deserializing them.
             * 
             * @param buffer: Serialized packet data to deserialize.
             * @return AdiosServerPacket object.
             */
            AdiosServerPacket(std::vector<char> &buffer);

            /**
             * @brief Destruct AdiosServerPacket object.
             */
            ~AdiosServerPacket();
        public:
            /**
             * @brief Serialize class data to binary to make it sendable by NetworkHandler.
             * 
             * @return empty std::vector<char> because nothing to serialize.
             */
            std::vector<char> serializeData() const override;
    };
}