/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "NetworkHandler.hpp"

namespace RType::Network {
    NetworkHandler::NetworkHandler() {};

    NetworkHandler::NetworkHandler(std::string host, unsigned int port, bool isServer)
    : _host(host), _port(port), _isServer(isServer) {};

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

    }
}
