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
        this->_endpointList.push_back(std::make_pair(serverEndpoint, true));
    }

    this->receiveData();
    this->_thread = std::thread([this] { this->_io_context.run(); });
}

NetworkHandler::~NetworkHandler() { this->_thread.join(); };

void NetworkHandler::resendValidationList()
{
    std::list<std::pair<const APacket &, const asio::ip::udp::endpoint &>> validationList =
        this->_packetHandler.getValidationList();
    for (auto &pairInLst : validationList)
    {
        this->sendData(pairInLst.first, pairInLst.second);
    }
}

void NetworkHandler::sendNewPacket(const APacket &packet, const asio::ip::udp::endpoint &endpoint)
{
    if (this->_packetHandler.needPacketValidation(packet))
        this->_packetHandler.insertToValidationList(packet, endpoint);
    this->sendData(packet, endpoint);
}

void NetworkHandler::popQueue() { this->_packetHandler.popReceiveQueue(); }

void NetworkHandler::sendData(const APacket &packet, const asio::ip::udp::endpoint &endpoint)
{
    std::vector<char> packetData;

    try
    {
        packetData = packet.serialize();
    }
    catch (APacket::PacketException &e)
    {
        std::cerr << "[sendData ERROR]: Problème de serialisation" << std::endl;
        return;
    }

    this->_socket->async_send_to(
        asio::buffer(packetData), endpoint,
        [this](std::error_code ec, std::size_t bytes_recvd)
        {
            if (ec)
            {
                std::cerr << "[sendData ERROR]: Problème de send de données" << std::endl;
                return;
            }
        });
}

void NetworkHandler::handleData(std::array<char, 1024> recvBuffer,
                                asio::ip::udp::endpoint remoteEndpoint)
{
    std::vector<char> buffer(recvBuffer.begin(), recvBuffer.end());
    std::shared_ptr<APacket> packet = nullptr;
    try
    {
        packet = this->_factory.createPacketFromBuffer(buffer);
    }
    catch (std::exception &e)
    {
        std::cerr << "[sendData ERROR]: Problème de deserialisation des packets" << std::endl;
        return;
    }
    this->_packetHandler.insertToReceiveQueue(packet, remoteEndpoint);
}

void NetworkHandler::receiveData()
{
    auto remoteEndpoint = std::make_shared<asio::ip::udp::endpoint>();

    this->_socket->async_receive_from(
        asio::buffer(_recvBuffer), *remoteEndpoint,
        [this, remoteEndpoint](std::error_code ec, std::size_t bytes_recvd)
        {
            if (!ec)
                this->handleData(_recvBuffer, *remoteEndpoint);
            else
                std::cerr << "[receiveData ERROR]: Problème de réception de données" << std::endl;
            return this->receiveData();
        });
}

void NetworkHandler::deleteFromValidationList(
    const std::shared_ptr<PacketValidationPacket> &validation,
    const asio::ip::udp::endpoint &endpoint)
{
    this->_packetHandler.deleteFromValidationList(validation, endpoint);
}

std::string NetworkHandler::getHost() const { return this->_host; }

unsigned int NetworkHandler::getPort() const { return this->_port; }

std::queue<std::pair<std::shared_ptr<APacket>, asio::ip::udp::endpoint>>
NetworkHandler::getPacketQueue() const
{
    return this->_packetHandler.getReceiveQueue();
}

bool NetworkHandler::getIsServer() const { return this->_isServer; }

void NetworkHandler::setHost(const std::string host) { this->_host = host; }

void NetworkHandler::setPort(const unsigned int port) { this->_port = port; }
}  // namespace RType::Network
