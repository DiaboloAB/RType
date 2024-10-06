/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#pragma once

#include <asio.hpp>
#include <iostream>
#include <list>
#include <string>
#include <thread>

#include <PacketManager/APacket.hpp>
#include <PacketManager/PacketFactory.hpp> 

namespace RType::Network
{
class NetworkHandler
{
   public:
    NetworkHandler() = delete;
    NetworkHandler(std::string host, unsigned int port, bool isServer);
    ~NetworkHandler();

   public:
    std::string getHost() const;
    unsigned int getPort() const;
    bool getIsServer() const { return this->_isServer; };
    void setHost(const std::string host);
    void setPort(const unsigned int port);

   public:
    void sendData(const APacket &packet, const asio::ip::udp::endpoint &endpoint);
    void receiveData();
    void handleData(std::array<char, 1024> recvBuffer, asio::ip::udp::endpoint remoteEndpoint);

   public:
    class NetworkHandlerError : public std::exception
    {
       public:
        NetworkHandlerError(std::string msg) : _msg(msg){};
        ~NetworkHandlerError(){};

       private:
        const char *what() const noexcept override { return _msg.c_str(); };

       private:
        std::string _msg;
    };

   public:
    std::string _host = "";
    unsigned int _port = 0;
    bool _isServer = false;
    std::list<asio::ip::udp::endpoint> _endpointList = {};
    asio::io_context _io_context;
    std::shared_ptr<asio::ip::udp::socket> _socket = nullptr;
    std::array<char, 1024> _recvBuffer;
    std::thread thread;
    PacketFactory _factory;
};
}  // namespace RType::Network