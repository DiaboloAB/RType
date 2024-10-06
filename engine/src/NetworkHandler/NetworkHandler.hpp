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
#include <queue>
#include <utility>

#include <PacketManager/APacket.hpp>
#include <PacketManager/PacketFactory.hpp> 

namespace RType::Network
{
class NetworkHandler
{
   public:
    
    NetworkHandler() = delete;

    /**
     * @brief Construct of Networkhandler class.
     *
     * @param host: Host of the game sever.
     * @param port: Port of the game server.
     * @param isServer: Status of the NetworkHandler (true if it's a server,
     * false else).
     * 
     * @return NetworkHandler object.
     */
    NetworkHandler(std::string host, unsigned int port, bool isServer);

    ~NetworkHandler();

   public:
    /**
     * @brief Getter for NetworkHandler server host.
     *
     * @return Host of the server.
     */
    std::string getHost() const;
    
    /**
     * @brief Getter for NetworkHandler server port.
     *
     * @return Port of the server.
     */
    unsigned int getPort() const;

    /**
     * @brief Getter for NetworkHandler packet queue.
     *
     * @return Packet queue of the NetworkHandler.
     */
    std::queue<std::pair<std::shared_ptr<RType::Network::APacket>, asio::ip::udp::endpoint>> getPacketQueue() const;

    /**
     * @brief Getter for NetworkHandler status.
     *
     * @return Status of the NetworkHandler.
     */
    bool getIsServer() const;


    void setHost(const std::string host);
    void setPort(const unsigned int port);

   public:

    /**
     * @brief Method that send packets from an endpoint to another using async method from asio network library.
     *
     * @param packet: Packet to send.
     * @param endpoint: Endpoint target to send packet to.
     */
    void sendData(const APacket &packet, const asio::ip::udp::endpoint &endpoint);

    /**
     * @brief Method that receive packets from an endpoint using async method from asio network library and send it to the handler.
     */
    void receiveData();

    /**
     * @brief Method called by receiveData to handle packets received and add it to NetworkHandler queue.
     * 
     * @param recvBuffer: Buffer of the packet received that will be deserialized.
     * @param remoteEndoint: Endpoint of the sender of the packet.
     */
    void handleData(std::array<char, 1024> recvBuffer, asio::ip::udp::endpoint remoteEndpoint);

    /**
     * @brief Method that pop the first element of packetQueue if not empty.
     */
    void popQueue();

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

   private:
    std::string _host = "";
    unsigned int _port = 0;
    bool _isServer = false;
    asio::io_context _io_context;
    std::shared_ptr<asio::ip::udp::socket> _socket = nullptr;
    std::array<char, 1024> _recvBuffer;
    std::thread thread;
    PacketFactory _factory;
    std::list<std::pair<asio::ip::udp::endpoint, bool>> _endpointList = {};
    std::queue<std::pair<std::shared_ptr<RType::Network::APacket>, asio::ip::udp::endpoint>> packetQueue;
};
}  // namespace RType::Network