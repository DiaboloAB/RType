/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "Server.hpp"

namespace RType::Server {

    Server::Server(int nb_args, char **flags) {
        try {
            if (nb_args % 2 != 1)
                throw ServerError("ServerError : Invalid number of arguments.");
            this->parseFlags(&flags[1], nb_args - 1);
        } catch (ServerError &e) {
            throw;
        }
    }

    Server::Server(const Server &obj) : _host(obj._host), _port(obj._port) {}

    Server::~Server() {}

    void Server::setHost(std::string const host) {
        this->_host = host;
    }

    std::string Server::getHost() {
        return this->_host;
    }

    unsigned int Server::getPort() {
        return this->_port;
    }

    void Server::setPort(const unsigned int port) {
        if (port < 1024 || port > 65535)
            throw ServerError("ServerError : Chose a port between 1024 and 65535.");
        this->_port = port;
    }

    void Server::parseFlags(char **flags, int nb_args) {
        try {
            for (size_t i = 0; i < nb_args; i += 2) {
                std::string flag = flags[i];
                if (flag == "-p" || flag == "--port")
                    this->setPort((unsigned int)std::stoi(flags[i + 1]));
                else if ((flag == "-H" || flag == "--host"))
                    this->setHost(flags[i + 1]);
                else
                    throw ServerError(std::string("ServerError: Unknown flag ") + flag);
            }
        } catch (ServerError &e) {
            throw;
        } catch (std::exception &e) {
            throw ServerError(std::string("ServerError : ") + e.what());
        }
    }

    Server &Server::operator=(const Server &obj) {
        if (&obj == this)
            return *this;
        this->_host = obj._host;
        this->_port = obj._port;
        return *this;
    }
}
