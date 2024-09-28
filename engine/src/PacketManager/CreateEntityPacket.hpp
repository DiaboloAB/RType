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
     * @class CreateEntityPacket
     * 
     * @brief Class used to create a Packet that can be serialize and deserialize. This packet hold
     * main information used to create new entities.
     */
    class CreateEntityPacket : public APacket {
        public:
            /**
             * @brief Construct CreateEntityPacket object that will be send to server or client.
             * 
             * @param entityId : Id of the entity that will be created.
             * @param posX : X position in the game at creation.
             * @param posY : Y position in the game at creation.
             * @param entityToCreate : Name of the prefab used to create entity.
             * @return CreateEntityPacket object.
             */
            CreateEntityPacket(uint32_t entityId, float posX, float posY, std::string entityToCreate);

            /**
             * @brief Destruct CreateEntityPacket object.
             */
            ~CreateEntityPacket() override;
        public:

            /**
             * @brief Serialize class data to binary to make it sendable by NetworkHandler.
             * 
             * @return std::vector<char> that represent serialization of entityId, posX, posY, entityToCreate to binary.
             */
            std::vector<char> serializeData() const override;
        private:
            uint32_t _entityId;
            float _posX;
            float _posY;
            std::string _entityToCreate;
    };
}
