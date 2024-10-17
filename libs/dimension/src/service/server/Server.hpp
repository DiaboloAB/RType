/**********************************************************************************
 *  Project: Dimension Network
 *  Description: Networking Game Library
 *  Author: Morgan LARGEOT, Maxence LARGEOT
 *  Create Time: 2024-10-17
 *  Location: Rennes
 **********************************************************************************/

#pragma once

#include <exception>
#include <string>

namespace dimension
{
class NetworkServer
{
   public:
    NetworkServer();
    ~NetworkServer();

   public:
    class NetworkServerError : public std::exception
    {
       public:
        NetworkServerError(std::string msg) : _msg(msg){};
        ~NetworkServerError(){};

       private:
        const char *what() const noexcept override { return _msg.c_str(); };

       private:
        std::string _msg;
    };

   private:
};
}  // namespace dimension
