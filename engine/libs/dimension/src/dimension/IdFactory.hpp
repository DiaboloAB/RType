/**********************************************************************************
 *   Project: Dimension Network
 *   Description: Networking Game Library
 *   Author: Morgan LARGEOT, Maxence LARGEOT
 *   Create Time: 2024-11-01
 *   Location: Rennes
 **********************************************************************************/

/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#pragma once

#include <cstdint>
#include <exception>
#include <queue>
#include <string>

namespace dimension
{

using NetworkId = uint32_t;
const NetworkId MAX_NID = 5000;

/**
 * @class IdFactory
 *
 * @brief This class is used by the server/room to assign a unique network ID to each entity it creates.
 * This network ID is provided to the client to facilitate communication between the client and the
 * server. It is used to manage various actions such as creating or destroying entities, among
 * others.
 */
class IdFactory
{
   public:
    IdFactory();
    ~IdFactory();

   public:
    /**
     * @brief Generates a unique network ID, either by reusing the ID of a destroyed entity or by
     * providing a new one.
     *
     * @return uint32_t representing the generated network ID.
     */
    uint32_t generateNetworkId();

    /**
     * @brief Add network Id to reusable Ids.
     */
    void becomeReusable(NetworkId reusable);

    class IdFactoryError : public std::exception
    {
       public:
        IdFactoryError(std::string msg) : _msg(msg){};
        ~IdFactoryError(){};

       private:
        const char *what() const noexcept override { return _msg.c_str(); };

       private:
        std::string _msg;
    };

   private:
    NetworkId _networkId = 0;
    std::queue<NetworkId> _reusable = {};
};
}  // namespace dimension