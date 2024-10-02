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
     * @class UpdateEntityPacket
     * 
     * @brief Class used to create a Packet that can be serialize and deserialize. This packet hold
     * main information used to update entities in game.
     */
    class UpdateEntityPacket : public APacket {
        public:
            /**
             * @brief Construct UpdateEntityPacket object that will be send to client.
             * 
             * @param entityId : Id of the entity that will be moved.
             * @param score : Score of the player
             * @return UpdateEntityPacket object.
             */
            UpdateEntityPacket(uint32_t entityId, uint32_t score);

            /**
             * @brief Construct new UpdateEntityPacket object with serialized data by deserializing them.
             * 
             * @param buffer: Serialized packet data to deserialize.
             * @return UpdateEntityPacket object.
             */
            UpdateEntityPacket(std::vector<char> &buffer);

            /**
             * @brief Destruct UpdateEntityPacket object.
             */
            ~UpdateEntityPacket() override;
        public:

            /**
             * @brief Serialize class data to binary to make it sendable by NetworkHandler.
             * 
             * @return std::vector<char> that represent serialization of entityId, score to binary.
             */
            std::vector<char> serializeData() const override;
        private:
            uint32_t _entityId;
            uint32_t _score;
    };
}
