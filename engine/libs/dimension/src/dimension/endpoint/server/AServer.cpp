/**********************************************************************************
 *  Project: Dimension Network
 *  Description: Networking Game Library
 *  Author: Morgan LARGEOT, Maxence LARGEOT
 *  Create Time: 2024-10-17
 *  Location: Rennes
 **********************************************************************************/

#include "AServer.hpp"

namespace dimension
{
AServer::AServer(const std::shared_ptr<PacketFactory> &factory, std::string host, unsigned int port)
    : AEndpoint(factory)
{
    this->_packetH[this->_packetFactory->getTypeFromIndex(std::type_index(typeid(
        ClientEvent)))] = [this](std::pair<std::shared_ptr<APacket>, asio::ip::udp::endpoint> pair)
    { return this->handleEvent(pair); };
    this->_packetH[this->_packetFactory->getTypeFromIndex(std::type_index(typeid(HiServer)))] =
        [this](std::pair<std::shared_ptr<APacket>, asio::ip::udp::endpoint> pair)
    { return this->handleHiServer(pair); };
    this->initServer(host, port);

}

void AServer::initServer(std::string host, unsigned int port) {
    try
    {
        this->_io_context = std::make_shared<asio::io_context>();
        asio::ip::udp::endpoint endpoint(asio::ip::udp::v4(), port);
        this->_socket = std::make_shared<asio::ip::udp::socket>(*this->_io_context, endpoint);
        this->receive();
        this->_recvThread =
            std::make_shared<std::thread>(std::thread([this] { this->_io_context->run(); }));
        std::cerr << "\x1B[32m[AServer]\x1B[0m: Server setup." << std::endl;
    }
    catch (std::exception &e)
    {
        std::cerr << "\x1B[31m[AServer ERROR]\x1B[0m: " << e.what() << std::endl;
    }
}

void AServer::run()
{
    while (true)
    {
        this->resendValidationList();
        std::queue<std::pair<std::shared_ptr<APacket>, asio::ip::udp::endpoint>> queueAtT =
            this->_rcvQueue;
        while (!queueAtT.empty())
        {
            auto &packet = queueAtT.front();
            auto function = this->_packetH.find(packet.first->getPacketType());
            if (!(function == this->_packetH.end())) function->second(packet);
            this->popReceiveQueue();
            queueAtT.pop();
        }
    }
}

void AServer::initRoom(asio::ip::udp::endpoint &sender, bool isPrivate)
{
    RoomState roomState;
    std::string roomCode = this->generateRoomCode();
    roomState._endpoints.push_back(sender);
    roomState._nbConnected += 1;
    roomState._port = this->getAvaiblePort();
    if (isPrivate)
        this->_privateRooms[roomCode] = roomState;
    else
        this->_rooms[roomCode] = roomState;
    std::cerr << "\x1B[32m[AServer]\x1B[0m: New room created : " << roomCode << std::endl;
}

void AServer::handleHiServer(std::pair<std::shared_ptr<APacket>, asio::ip::udp::endpoint> &packet)
{
    auto hiClient = this->_packetFactory->createEmptyPacket<HiClient>();
    if (!this->isConnected(packet.second))
    {
        this->_connectedEp.emplace_back(packet.second);
        std::cerr << "\x1B[32m[AServer]\x1B[0m: New connection received." << std::endl;
    }
    this->send(hiClient, packet.second);
}

void AServer::handleEvent(std::pair<std::shared_ptr<APacket>, asio::ip::udp::endpoint> &packet)
{
    if (!isConnected(packet.second)) return;
    try {
        std::shared_ptr<ClientEvent> event = std::dynamic_pointer_cast<ClientEvent>(packet.first);
        if (event->getClientEvent() != ROOM) return;
        std::string eventDesc = event->getDescription();
        if (eventDesc == "cr") return this->initRoom(packet.second);
        if (eventDesc == "crp") return this->initRoom(packet.second, true);
        std::cerr << "\x1B[31m[AServer Error]\x1B[0m: unknown event : " << eventDesc << std::endl;
        auto validation = this->_packetFactory->createEmptyPacket<PacketValidation>();
        validation->setPacketReceiveTimeStamp(packet.first->getPacketTimeStamp());
        validation->setPacketReceiveType(packet.first->getPacketType());
        this->send(validation, packet.second, false);
    } catch (std::exception &e) {
        std::cerr << "\x1B[31m[AServer Error]\x1B[0m: Error in client event {" << e.what() << "}" << std::endl;
    }
}

bool AServer::isConnected(asio::ip::udp::endpoint &endpoint) const
{
    for (auto &connected : this->_connectedEp)
        if (connected == endpoint) return true;
    return false;
}

unsigned int AServer::getAvaiblePort() const
{
    asio::io_context io_context;
    asio::ip::udp::socket socket(io_context);
    asio::ip::udp::endpoint endpoint(asio::ip::udp::v4(), 0);
    socket.open(endpoint.protocol());
    socket.bind(endpoint);
    unsigned int port = (unsigned int)socket.local_endpoint().port();
    socket.close();
    return port;
}

std::string AServer::generateRoomCode() const
{
    const std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::string roomCode;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, chars.size() - 1);
    for (int i = 0; i < 6; i++) roomCode += chars[distrib(gen)];
    return roomCode;
}
}  // namespace dimension