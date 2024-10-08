/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#pragma once

#include <NetworkHandler/PacketHandler.hpp>
#include <PacketManager/APacket.hpp>
#include <PacketManager/PacketFactory.hpp>
#include <asio.hpp>
#include <iostream>
#include <list>
#include <queue>
#include <string>
#include <thread>
#include <utility>
#include <map>

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
     * @brief Send all keeped packet that need a validation to avoid broken game due to missing
     * packets.
     */
    void resendValidationList();

    /**
     * @brief Send a completely new packet to client or server and add it to a validation list if
     * packet needs it.
     *
     * @param packet: Packet to send (HiServer, ...).
     * @param endpoint: Endpoint target to send packet to.
     */
    void sendNewPacket(const APacket &packet, const asio::ip::udp::endpoint &endpoint);

    /**
     * @brief Getter for NetworkHandler endpoint list.
     *
     * @return Endpoint list of the NetworkHandler.
     */
    std::map<asio::ip::udp::endpoint, bool> getEndpointMap() const;

   public:
    /**
     * @brief Method that send packets from an endpoint to another using async method from asio
     * network library.
     *
     * @param packet: Packet to send.
     * @param endpoint: Endpoint target to send packet to.
     */
    void sendData(const APacket &packet, const asio::ip::udp::endpoint &endpoint);

    /**
     * @brief Method that receive packets from an endpoint using async method from asio network
     * library and send it to the handler.
     */
    void receiveData();

    /**
     * @brief Method called by receiveData to handle packets received and add it to NetworkHandler
     * queue.
     *
     * @param recvBuffer: Buffer of the packet received that will be deserialized.
     * @param remoteEndoint: Endpoint of the sender of the packet.
     */
    void handleData(std::array<char, 1024> recvBuffer, asio::ip::udp::endpoint remoteEndpoint);

    /**
     * @brief Method that pop the first element of packetQueue if not empty.
     */
    void popQueue();

    /**
     * @brief Delete packet keeped in validation list if a validation of this packet is received.
     * Does nothing if the validation correspond to any packet in the packet validation list.
     *
     * @param validation: Packet that tells information about the packet it validate.
     * @param enpoint: Enpoint target that receives the validated packet.
     */
    void deleteFromValidationList(const std::shared_ptr<PacketValidationPacket> &validation,
                                  const asio::ip::udp::endpoint &endpoint);


    /**
     * @brief Update value of the key element (endpoint) in the map if it exist. 
     * Add it to map else.
     *
     * @param endpoint: Key of the map element.
     * @param value: New value of the element.
     */
    void updateEndpointMap(asio::ip::udp::endpoint endpoint, bool value);

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
    std::string getHost() const;
    unsigned int getPort() const;
    bool getIsServer() const;
    std::queue<std::pair<std::shared_ptr<RType::Network::APacket>, asio::ip::udp::endpoint>>
    getPacketQueue() const;

   public:
    void setHost(const std::string host);
    void setPort(const unsigned int port);

   private:
    std::string _host = "";
    unsigned int _port = 0;
    bool _isServer = false;
    std::array<char, 1024> _recvBuffer;
    asio::io_context _io_context;
    std::shared_ptr<asio::ip::udp::socket> _socket = nullptr;
    std::map<asio::ip::udp::endpoint, bool> _endpointMap = {};
    std::thread _thread;
    PacketFactory _factory;
    PacketHandler _packetHandler;
};
}  // namespace RType::Network