/**********************************************************************************
 *  Project: Dimension Network
 *  Description: Networking Game Library
 *  Author: Morgan LARGEOT, Maxence LARGEOT
 *  Create Time: 2024-10-17
 *  Location: Rennes
  **********************************************************************************/

#pragma once

#include <asio.hpp>

namespace dimension {
    class IService {
        public:
            ~IService() = default;
        public:
            virtual void sendPacket();
            virtual void receivePackets();
            

    };
}