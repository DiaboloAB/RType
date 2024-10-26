/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "MainServer.hpp"

namespace RType::Network {
MainServer::MainServer(std::string host, unsigned int port) : 
    dimension::AServer(std::make_shared<dimension::PacketFactory>(), host, port) 
{
    this->registerEventHandling("cr=pv", 
        [this](asio::ip::udp::endpoint &sender, std::string &desc) { return this->initRoom(sender, desc); });
}

MainServer::~MainServer() {}

void MainServer::initRoom(asio::ip::udp::endpoint &sender, std::string &description)
{
    RoomState roomState;
    std::string roomCode = this->generateRoomCode();
    roomState._endpoints.push_back(sender);
    roomState._nbConnected += 1;
    roomState._port = this->getAvaiblePort();
    if (description != "cr=pv" && description != "rd") {
        std::cerr << "\x1B[31m[MainServer Error]\x1B[0m: invalid room creation command." << std::endl;
        return;
    }
    if (description == "cr=pv")
        this->_privateRooms[roomCode] = roomState;
    else if (description == "cr=rd")
        this->_rooms[roomCode] = roomState;
    std::cerr << "\x1B[32m[MainServer]\x1B[0m: New room created : " << roomCode << std::endl;
}


void MainServer::joinRoom(asio::ip::udp::endpoint &sender, std::string &description)
{
    return;
}

void MainServer::startRoom(asio::ip::udp::endpoint &sender, std::string &description)
{
    return;
}

void MainServer::endRoom(asio::ip::udp::endpoint &sender, std::string &description)
{
    return;
}

std::string MainServer::generateRoomCode() const
{
    const std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::string roomCode;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, chars.size() - 1);
    for (int i = 0; i < 6; i++) roomCode += chars[distrib(gen)];
    return roomCode;
}

unsigned int MainServer::getAvaiblePort() const
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
}
