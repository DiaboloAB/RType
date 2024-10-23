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

namespace RType::Network
{

using NetworkId = uint32_t;
const NetworkId MAX_NID = 5000;

/**
 * @class NetworkIdHandler
 *
 * @brief This class is used by the server to assign a unique network ID to each entity it creates.
 * This network ID is provided to the client to facilitate communication between the client and the
 * server. It is used to manage various actions such as creating or destroying entities, among
 * others.
 */
class NetworkIdHandler
{
   public:
    NetworkIdHandler();
    ~NetworkIdHandler();

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

    class NetworkIdHandlerError : public std::exception
    {
       public:
        NetworkIdHandlerError(std::string msg) : _msg(msg) {};
        ~NetworkIdHandlerError() {};

       private:
        const char *what() const noexcept override { return _msg.c_str(); };

       private:
        std::string _msg;
    };

   private:
    NetworkId _networkId = 0;
    std::queue<NetworkId> _reusable = {};
};

}  // namespace RType::Network