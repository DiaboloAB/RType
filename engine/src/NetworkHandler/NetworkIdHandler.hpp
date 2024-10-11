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

class NetworkIdHandler
{
   public:
    NetworkIdHandler();
    ~NetworkIdHandler();

   public:
    uint32_t generateNetworkId();
    void becomeReusable(NetworkId reusable);

    class NetworkIdHandlerError : public std::exception
    {
       public:
        NetworkIdHandlerError(std::string msg) : _msg(msg){};
        ~NetworkIdHandlerError(){};

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