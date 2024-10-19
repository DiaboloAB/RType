/**********************************************************************************
 *  Project: Dimension Network
 *  Description: Networking Game Library
 *  Author: Morgan LARGEOT, Maxence LARGEOT
 *  Create Time: 2024-10-17
 *  Location: Rennes
  **********************************************************************************/

#include "Client.hpp"

namespace dimension {
    DimensionClient::DimensionClient(std::shared_ptr<APacketFactory> &factory) : AEndpoint(factory) {}

    DimensionClient::~DimensionClient()
    {
        if (this->_io_context)
            this->_io_context->stop();
        if (this->_recvThread)
            this->_recvThread->join();
    }

    void DimensionClient::connectServer(std::string host, unsigned int port)
    {
        try {
            this->_io_context = std::make_shared<asio::io_context>();
            asio::ip::udp::endpoint endpoint(asio::ip::udp::v4(), 0);
            if (!this->_io_context)
                std::cerr << "io null" << std::endl;
            std::cerr << endpoint.address() << " " << endpoint.port() << std::endl;
            std::cerr << "SEGV" << std::endl;
            this->_socket = std::make_shared<asio::ip::udp::socket>(*this->_io_context, endpoint);
            std::cerr << "SEGV" << std::endl;
            asio::ip::udp::resolver resolver(*this->_io_context);
            std::cerr << "SEGV" << std::endl;
            asio::ip::udp::resolver::results_type endpoints = resolver.resolve(asio::ip::udp::v4(), host, std::to_string(port));
            std::cerr << "SEGV" << std::endl;
            this->_serverEndpoint = std::make_shared<asio::ip::udp::endpoint>(*endpoints.begin());
            std::cerr << "SEGV" << std::endl;
            this->receive();
            std::cerr << "SEGV" << std::endl;
            this->_recvThread = std::make_shared<std::thread>(std::thread([this] { this->_io_context->run(); }));
            std::cerr << "SEGV" << std::endl;
            std::cerr << "\x1B[32m[DimensionClient]\x1B[0m: Connection to server established." << std::endl;
        } catch (std::exception &e) {
            std::cerr << "-------------------------------------------------------------" << std::endl;
            std::cerr << e.what() << std::endl;
            std::cerr << "-------------------------------------------------------------" << std::endl;
        }
    }

    void DimensionClient::handleDataReceived(std::array<char, 1024> &buffer,
                asio::ip::udp::endpoint &endpoint, std::size_t &bytesRcv)
    {
        return;
    }
}
