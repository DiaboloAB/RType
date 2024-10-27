/**********************************************************************************
 *  Project: Dimension Network
 *  Description: Networking Game Library
 *  Author: Morgan LARGEOT, Maxence LARGEOT
 *  Create Time: 2024-10-17
 *  Location: Rennes
 **********************************************************************************/

#pragma once

#include <list>
#include <memory>
#include <random>

#include "AEndpoint.hpp"
#include "ClientEventType.hpp"
#include "PacketFactory.hpp"

namespace dimension
{
/**
 * @class AServer
 * 
 * @brief Network server of the dimension library 
 */
class AServer : public AEndpoint
{
   public:
    AServer(const std::shared_ptr<PacketFactory> &factory, std::string host, unsigned int port);
    ~AServer() = default;

   public:
    /**
     * @brief Run of the server that take packet queue and send packets to associated handlers.
     */
    void run();

   private:
   /**
    * @brief Init all server attributes needed with the uses of ASIO library and run the server.
    * 
    * @param host: Host of the server.
    * @param port: Port of the server.
    */
    void initServer(std::string host, unsigned int port);

   private:
    /**
    * @brief Handler for the ClientEvent default packet.
    * 
    * @param packet: ClientEvent default packet.
    */
    void handleEvent(std::pair<std::shared_ptr<APacket>, asio::ip::udp::endpoint> &packet);
    /**
     * @brief Handler for the HiServer default packet.
     * 
     * @param packet HiServer default packet.
     */
    void handleHiServer(std::pair<std::shared_ptr<APacket>, asio::ip::udp::endpoint> &packet);

   protected:
    using EventFunction = std::function<void(asio::ip::udp::endpoint &, std::string &)>;
    using PacketHandler =
        std::function<void(std::pair<std::shared_ptr<APacket>, asio::ip::udp::endpoint> &)>;

   protected:
    /**
     * @brief Add custom client events into event handler list.
     * 
     * @param desc: Description of the event.
     * @param handler: Handler associted to the event.
     */
    void registerEventHandling(std::string desc, EventFunction handler);

    /**
     * @brief Check if a client is connected to the server.
     * 
     * @param endpoint: Endpoint of the client to ckeck.
     * @return true 
     * @return false 
     */
    bool isConnected(asio::ip::udp::endpoint &endpoint) const;

   protected:
    std::list<asio::ip::udp::endpoint> _connectedEp;
    std::unordered_map<uint8_t, PacketHandler> _packetH;
    std::unordered_map<std::string, EventFunction> _eventH;
};
}  // namespace dimension
