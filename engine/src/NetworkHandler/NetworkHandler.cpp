/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "NetworkHandler.hpp"

namespace RType::Network {
    NetworkHandler::NetworkHandler(std::string host, unsigned int port, bool isServer)
    : _host(host), _port(port), _isServer(isServer), _io_context() {
        this->_socket = std::make_shared<asio::ip::udp::socket>(_io_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), isServer ? port : 0));
        this->receiveData();
        this->_io_context.run();
    };

    NetworkHandler::~NetworkHandler() {};

    std::string NetworkHandler::getHost() const {
        return this->_host;
    }

    unsigned int NetworkHandler::getPort() const {
        return this->_port;
    }

    void NetworkHandler::setHost(const std::string host) {
        this->_host = host;
    }

    void NetworkHandler::setPort(const unsigned int port) {
        this->_port = port;
    }

    void NetworkHandler::sendData() {

    }

    void NetworkHandler::receiveData() {
        this->_socket->async_receive_from(
        asio::buffer(recv_buffer_), remote_endpoint_,
        std::bind(&udp_server::handle_receive, this,
          asio::placeholders::error,
          asio::placeholders::bytes_transferred));
    }
}
