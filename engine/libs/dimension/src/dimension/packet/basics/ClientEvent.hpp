/**********************************************************************************
 *  Project: Dimension Network
 *  Description: Networking Game Library
 *  Author: Morgan LARGEOT, Maxence LARGEOT
 *  Create Time: 2024-10-20
 *  Location: Rennes
 **********************************************************************************/

#pragma once

#include "APacket.hpp"

namespace dimension
{
/**
 * @class ClientEvent
 *
 * @brief Class used to create a Packet that can be serialize and deserialize. This packet hold
 * main information used to manage client events (shoot, move, ...).
 */
class ClientEvent : public dimension::APacket
{
   public:
    /**
     * @brief Construct ClientEvent object that will be send to sever.
     *
     * @param type packet type define by class index in packetManager registration.
     * @return empty ClientEvent object.
     */
    ClientEvent(uint8_t type);

    /**
     * @brief Construct new ClientEvent object with serialized data by deserializing them.
     *
     * @param buffer: Serialized packet data to deserialize.
     * @return ClientEvent object.
     */
    ClientEvent(std::vector<char> &buffer);

    /**
     * @brief Destruct ClientEvent object.
     */
    ~ClientEvent();

   public:
    /**
     * @brief Serialize class data to binary to make it sendable by NetworkHandler.
     *
     * @return std::vector<char> representing the serialization of _clientEvent to binary.
     */
    std::vector<char> serializeData() const override;

   public:
    uint8_t getClientEvent() const;
    std::string getDescription() const;

   public:
    void setClientEvent(const uint8_t &event);
    void setDescription(const std::string &description);

   private:
    uint8_t _clientEvent;
    std::string _description;
};
}  // namespace dimension
