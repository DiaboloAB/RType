/**********************************************************************************
 *  Project: Dimension Network
 *  Description: Networking Game Library
 *  Author: Morgan LARGEOT, Maxence LARGEOT
 *  Create Time: 2024-10-17
 *  Location: Rennes
  **********************************************************************************/

#include "Server.hpp"

namespace dimension {
DimensionServer::DimensionServer(std::shared_ptr<APacketFactory> &factory, std::string host, unsigned int port)
    : AEndpoint(factory) 
{
  try {
    this->_io_context = std::make_shared<asio::io_context>();
    asio::ip::udp::endpoint endpoint(asio::ip::udp::v4(), port);
    this->_socket = std::make_shared<asio::ip::udp::socket>(*this->_io_context, endpoint);
    this->receive();
    this->_recvThread = std::make_shared<std::thread>(std::thread([this] { this->_io_context->run(); }));
    std::cerr << "\x1B[32m[DimensionServer]\x1B[0m: Server setup." << std::endl;
  } catch (std::exception &e) {
      std::cerr << "\x1B[31m[DimensionServer ERROR]\x1B[0m: "<< e.what() << std::endl;
  }
}

void DimensionServer::handlePackets() 
{
  std::queue<std::pair<std::shared_ptr<APacket>, asio::ip::udp::endpoint>> queueAtT = this->_rcvQueue;
  while (!queueAtT.empty()) {
    auto &packet = queueAtT.front();
  }
}

void DimensionServer:: sendToRoom(std::pair<std::shared_ptr<APacket>, asio::ip::udp::endpoint> &packet)
{
  for (auto &room : this->_matchMakingRoom) {
    if (room->endpointInRoom(packet.second)) {
      room->addToReceiveQueue(packet.first, packet.second);
      return;
    }
  }
  for (auto &room : this->_privateRoom) {
    if (room->endpointInRoom(packet.second)) {
      room->addToReceiveQueue(packet.first, packet.second);
      return;
    }
  }
  std::shared_ptr<PacketValidation> validation = this->_packetFactory->createEmptyPacket<PacketValidation>();
  validation->setPacketReceiveTimeStamp(packet.first->getPacketTimeStamp());
  validation->setPacketReceiveType(packet.first->getPacketType());
  this->send(validation, packet.second, false);
}
}