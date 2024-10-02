/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "NetworkHandler.hpp"

namespace RType::Network
{
NetworkHandler::NetworkHandler(std::string host, unsigned int port, bool isServer)
    : _host(host), _port(port), _isServer(isServer), _io_context()
{
    asio::ip::udp::endpoint endpoint(asio::ip::udp::v4(), isServer ? port : 0);
    this->_socket = std::make_shared<asio::ip::udp::socket>(_io_context, endpoint);

    if (!isServer)
    {
        asio::ip::udp::resolver resolver(this->_io_context);
        asio::ip::udp::resolver::results_type endpoints =
            resolver.resolve(host, std::to_string(port));
        asio::ip::udp::endpoint serverEndpoint = *endpoints.begin();
        this->_endpointList.push_back(serverEndpoint);
    }

    this->receiveData();
    this->thread = std::thread([this] { this->_io_context.run(); });
}

NetworkHandler::~NetworkHandler() { this->thread.join(); };

std::string NetworkHandler::getHost() const { return this->_host; }

unsigned int NetworkHandler::getPort() const { return this->_port; }

void NetworkHandler::setHost(const std::string host) { this->_host = host; }

void NetworkHandler::setPort(const unsigned int port) { this->_port = port; }

void NetworkHandler::sendData(const APacket &packet, const asio::ip::udp::endpoint &endpoint)
{

}

void NetworkHandler::handleData(std::array<char, 1024> recvBuffer,
                                asio::ip::udp::endpoint remoteEndpoint)
{
    std::cout << "De la data!" << std::endl;
}

void NetworkHandler::receiveData()
{
    auto remoteEndpoint = std::make_shared<asio::ip::udp::endpoint>();

    this->_socket->async_receive_from(
        asio::buffer(_recvBuffer), *remoteEndpoint,
        [this, remoteEndpoint](std::error_code ec, std::size_t bytes_recvd)
        {
            if (!ec)
            {
                this->handleData(_recvBuffer, *remoteEndpoint);
                return this->receiveData();
            }
            else
                throw NetworkHandlerError("NetworkHandler Error: Corrupted packets");
        });
}
}  // namespace RType::Network
